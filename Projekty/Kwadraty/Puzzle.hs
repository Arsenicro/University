-- ----------------------------------------------------------------------------
-- Puzzle.hs
-- WERSJA 0.1
-- ZADANIE 1 (Kwadraty)
-- ----------------------------------------------------------------------------
module Puzzle where

data Puzzle = Puzzle Int Int [(Int, Int, Int)]
type Result = [(Int, Int, Int)]
type Solver = Int -> Int -> [(Int, Int, Int)] -> [Result]

data Test
    = SimpleTest Puzzle Result
    | CountTest  Puzzle Int

runSolver :: Solver -> Puzzle -> [Result]
runSolver solver (Puzzle m n l) = solver m n l

checkSolution :: Result -> Result -> Bool
checkSolution = ( == )

baseTests :: [Test]
baseTests =
    [ SimpleTest
        (Puzzle 7 7 [(3,3,0), (3,5,0), (4,4,1), (5,1,0), (6,6,3)])
        [(1,1,2), (1,5,2), (4,4,3), (5,1,2), (2,2,4)]
    , CountTest
        (Puzzle 7 7 [(3,3,0), (3,5,0), (4,4,1), (5,1,0), (6,6,3)])
        1
    , SimpleTest
        (Puzzle 3 3 [(2,2,0)])
        [(2,1,1)]
    , SimpleTest
        (Puzzle 4 4 [(1,1,0), (4,4,0)])
        [(1,1,1), (3,3,1)]
    , SimpleTest
        (Puzzle 4 4 [(1,1,0), (4,4,0)])
        [(1,1,2), (2,2,2)]
    , CountTest
        (Puzzle 4 4 [(1,1,0), (4,4,0)])
        2
    , CountTest
        (Puzzle 3 3 [(1,3,0),(3,1,0)])
        0
    , SimpleTest
        (Puzzle 12 12
            [(4,3,0),  (7,3,0),  (10,3,0), (4,4,1),  (3,5,2),  (9,5,2), 
            (10,6,1),  (11,7,4), (5,9,1),  (3,10,1), (6,10,1), (2,11,3),
            (11,10,1), (10,11,1)])
        [(2,1,2), (7,2,1), (9,2,1),  (1,4,3), (3,2,3), (9,5,3),  (8,4,2),
        (5,1,6), (5,9,3), (1,10,2), (4,8,2), (2,6,5), (9,10,2), (10,9,2)]
    ]