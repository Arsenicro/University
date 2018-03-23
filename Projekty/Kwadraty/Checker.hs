-- Checker.hs
-- WERSJA 0.2
-- ----------------------------------------------------------------------------
module Checker(checkerMain) where

import Puzzle

import Control.Exception as C
import Data.Maybe
import qualified System.Timeout

-- Jeśli chcesz by był wyświetlany czas działania programu, to:
-- 1. zainstaluj pakiet timeit:
--    $ cabal install timeit
-- 2. odkomentuj następny wiersz:
-- import System.TimeIt
-- 3. zakomentuj następny wiersz:
timeIt = id

-- Tutaj wybierz czas na jaki jest uruchamiany jeden test
-- Just t  oznacza uruchomienie na t sekund
-- Nothing oznacza oczekiwanie na zakończenie działania
timeout :: Maybe Int
timeout = Just 5

checkerMain :: Solver -> [Test] -> IO ()
checkerMain solve studentTests = do
    runAllTests solve studentTests -- Uruchomienie testów studenta
    runAllTests solve baseTests    -- Uruchomienie testów bazowych
    return ()

-- ============================================================================

data Status = Accept | WrongAnswer | TimeLimitExceeded | RuntimeError
    deriving Eq

statusString :: Status -> String
statusString Accept            = "Accept!"
statusString WrongAnswer      = "Wrong answer!"
statusString TimeLimitExceeded = "Time limit exceeded!"
statusString RuntimeError      = "RuntimeError!"

runWithTimeout :: (Maybe Int) -> Bool -> IO (Maybe Bool)
runWithTimeout Nothing  = fmap Just . timeIt . C.evaluate
runWithTimeout (Just t) =
    System.Timeout.timeout (t * 1000000) . timeIt . C.evaluate

getStatus :: IO (Maybe Bool) -> IO Status
getStatus x =
    fmap toStatus x
    `C.catch`
    ((\ _ -> return RuntimeError) :: C.SomeException -> IO Status)
    where
        toStatus Nothing      = TimeLimitExceeded
        toStatus (Just True)  = Accept
        toStatus (Just False) = WrongAnswer

runTestLazy :: Solver -> Test -> Bool
runTestLazy solve (SimpleTest puzzle result) =
    any (checkSolution result) $ runSolver solve puzzle
runTestLazy solve (CountTest puzzle count) =
    length (runSolver solve puzzle) == count

runTest :: Solver -> Test -> IO Bool
runTest solve test = do
    status <- getStatus $ runWithTimeout timeout $ runTestLazy solve test
    putStrLn $ statusString status
    return (status == Accept)

runAllTestsLoop :: Solver -> [Test] -> Int -> Int -> Int -> IO Int
runAllTestsLoop solve []    i n accepted = return accepted
runAllTestsLoop solve (t:ts) i n accepted = do
    putStrLn "======================"
    putStrLn ("Test: " ++ show i ++ "/" ++ show n)
    status <- runTest solve t
    runAllTestsLoop solve ts (i+1) n (if status then accepted+1 else accepted)

runAllTests :: Solver -> [Test] -> IO Bool
runAllTests solve tests = do
    accepted <- runAllTestsLoop solve tests 1 (length tests) 0
    putStrLn ("Accepted: " ++ show accepted ++ "/" ++ show (length tests))
    return $ accepted == length tests