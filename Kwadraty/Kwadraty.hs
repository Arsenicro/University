{-
Kamil Matuszewski. Numer indeksu: 272331.

Zadanie: Kwadraty
-}
import Puzzle
import Checker

type Liczba = (Int,Int,Int)
type Kwadrat = (Int,Int,Int)

tests :: [Test]
tests = [SimpleTest
        (Puzzle 4 5 [(2,2,1), (3,3,1)])
        [(2,2,2), (1,1,2)]
	, SimpleTest
        (Puzzle 6 7 [(3,3,0), (3,4,0),(4,4,0),(4,3,1),(5,2,4)])
        [(1,1,2),(1,4,2),(4,4,2),(4,1,2),(2,2,3)]
	, SimpleTest
        (Puzzle 13 13 [(5,8,1),(4,4,1),(9,9,1),(5,5,1),(8,8,1),(4,9,1),(9,4,1),(11,11,8),(1,1,9),(8,5,1)])
        [(3,8,2),(4,4,2),(7,7,2),(3,3,2),(8,8,2),(4,7,2),(7,4,2),(2,2,9),(1,1,11),(8,3,2)]	
	, SimpleTest
        (Puzzle 5 5 [(1,1,0),(5,5,0)])
        [(1,1,1),(3,3,2)]
	, SimpleTest
        (Puzzle 199 199 [(98,98,0)])
		[(1,1,97)]
	, CountTest
        (Puzzle 5 5 [(1,1,1),(5,5,1),(2,2,0)])
        0
	, CountTest
        (Puzzle 6 7 [(3,3,0),(3,4,0),(4,4,0),(4,3,1),(5,2,4)])
        1
	, CountTest
        (Puzzle 13 13 [(5,8,1),(4,4,1),(9,9,1),(5,5,1),(8,8,1),(4,9,1),(9,4,1),(11,11,8),(1,1,9),(8,5,1)])
        4
	, CountTest
        (Puzzle 20 20 [(5,8,1),(4,4,1),(9,9,1),(5,5,1),(8,8,1),(4,9,1),(9,4,1),(1,1,9),(2,2,5),(17,15,1),(19,18,3),(8,5,1), (10,10,2), (15,14,5), (18,17,4), (15,19,2),(20,20,20)])
        0
	, CountTest
        (Puzzle 200 200 [(1,1,0)])
        199
    ]

main :: IO ()
main = checkerMain solve tests

solve :: Int -> Int -> [(Int, Int, Int)] -> [Result]
solve m n lista = solve_alpha ( generuj_liste_kandydatow m n lista)

{-

solve_alpha pobiera liste kandydatow na rozwiazanie. Nastepnie wybiera jakis element z pierwszej listy i filtruje pozostale listy z pomoca czy_nienachodzi. Powtarza ten proces wybierajac po jednym kandydacie z kazdej listy, ostatecznie zwracajac liste rozwiazan, i powtarza proces poki ma z czego wybierac, tworzac liste list rozwiazan.
-}

solve_alpha:: [[Kwadrat]] -> [[Kwadrat]]
solve_alpha [] = [[]]
solve_alpha (k:ks) =  concat (map (\x -> let ys = solve_alpha (map (filter (czy_nienachodzi x)) ks) in map (\xs -> x:xs) ys) k)

{-

generuj_liste_kandydatow - prawie glowny predykat, przyjmuje ilosc wierszy i kolumn oraz liste cyfr, i zwraca liste list: dla kazdej cyfry z listy zwraca liste potencjalnych kandydatow na rozwiazanie.

-}
generuj_liste_kandydatow :: Int -> Int -> [Liczba] ->[[Kwadrat]]
generuj_liste_kandydatow m_wiersz m_kolumna liczby = map (lepsza_lista m_wiersz m_kolumna liczby) liczby

{-

lepsza_lista, przyjmuje ilosc wierszy i kolumn oraz liste liczb i liczbe dla ktorej tworzymy kwadrat. Najpierw tworzy kwadraty za pomoca funkcji lista, nastepnie filtruje ja wzgledem zawierania na swoich brzegach jakichs liczb, a na koniec zwraa tylko te liczby, dla ktorych liczba elementow w srodku zgadza sie z wartoscia liczby.

-}

lepsza_lista :: Int -> Int -> [Liczba] -> Liczba -> [Kwadrat]
lepsza_lista m_wiersz m_kolumna list (w,k,c) = filtr_liczb kwadraty list c where kwadraty = filter (czy_niezawiera (lista_bez_liczby list (w,k,c))) (lista m_wiersz m_kolumna (w,k,c))


{-

lista_bez_liczby pobiera liste liczb i liczbe i zwraca ta sama liste pozbawiona elementu liczba.

-}
	
lista_bez_liczby :: [Liczba] -> Liczba -> [Liczba]
lista_bez_liczby xs (w,k,c) = filter (czy_rozne (w,k,c)) xs

{-

lista - pomocnicza funkcja, przyjmuje ilosc kolumn i wierszy oraz liczbe, dla ktorej tworzy wszystkie czesciowo poprawne kwadraty (w tym takie ktore wiersz badz kolumne maja rowna 0, oraz takie ktore wewnatrz siebie nie maja odpowiedniej ilosci liczb.

-}

lista :: Int -> Int -> Liczba -> [Kwadrat]
lista m_wiersz m_kolumna (wiersz,kolumna,d) = gl++gp++dl++dp where 
	gl = generuj_gora_lewo ((min wiersz kolumna)) (wiersz,kolumna,d)
	dl = generuj_dol_lewo ((min (m_wiersz-wiersz) kolumna)) (wiersz,kolumna,d)
	gp = generuj_gora_prawo ((min wiersz (m_kolumna - kolumna))) (wiersz,kolumna,d)
	dp = generuj_dol_prawo (min (m_wiersz - wiersz) (m_kolumna - kolumna)) (wiersz,kolumna,d)

{-

filtr_liczb = przyjmuje liste kwadratow, liste liczb oraz liczbe. Zwraca liste kwadratow ktore wewnatrz siebie maja dokladnie tyle liczb ile wynosi wartosc "liczba"

-}

filtr_liczb :: [Kwadrat] -> [Liczba] -> Int -> [Kwadrat]
filtr_liczb kwadrat liczby liczba = filter (czy_dobry liczby liczba) kwadrat

{-

czy_dobry przyjmuje liste liczb, liczbe i kwadrat i wzraca true jesli w kwadracie jest dokladnie tyle liczb ile wynosi wartosc "liczba"

-}

czy_dobry :: [Liczba] -> Int -> Kwadrat -> Bool
czy_dobry list liczba kwadrat
	| (ile_w_srodku kwadrat list == liczba) = True
	| otherwise = False

	
{-

ile_w_srodku przyjmuje kwadrat i liste liczb i zwraca ilosc liczb wewnatrz kwadratu

-}
	
ile_w_srodku :: Kwadrat -> [Liczba] -> Int
ile_w_srodku _ [] = 0
ile_w_srodku kwadrat (x:xs)
	| (czy_w_srodku kwadrat x == True) = 1 + ile_w_srodku kwadrat xs
	| otherwise = ile_w_srodku kwadrat xs

{-

czy_w_srodku przyjmuje kwadrat i liczbe, i sprwdza czy dana liczba znajduje sie w srodku kwadratu

-}
	
czy_w_srodku :: Kwadrat -> Liczba -> Bool
czy_w_srodku (w,k,d) (wiersz,kolumna,_)
	| (wiersz>w && wiersz<(w+d) && kolumna>k && kolumna<(k+d)) = True
	| otherwise = False

{-

czy_rozne zwraca true jesli dwa elementy typu liczba sa rozne.

-}

czy_rozne :: Liczba -> Liczba -> Bool
czy_rozne (w,k,c) (wiersz,kolumna,liczba)
	| (w==wiersz && k==kolumna && c==liczba) = False
	| otherwise = True


{-

czy_niezawiera przyjmuje liste liczb i kwadrat. Zwraca true wtedy i tylko wtedy kiedy na brzegu kwadratu nie lezy zadna liczba z listy oraz jesli liczba nie ma wiersza badz kolumny rownej 0.

-}	

	
czy_niezawiera :: [Liczba] -> Kwadrat -> Bool
czy_niezawiera [] (wiersz,kolumna,_)
	| (wiersz==0) || (kolumna==0) = False
	| otherwise = True
czy_niezawiera ((w,k,_):xs) (wiersz,kolumna,d)
	| (wiersz==0) || (kolumna==0) = False
	| (w==wiersz && k<=(kolumna+d) && k>=kolumna) = False
	| (w==(wiersz+d) && k<=(kolumna+d) && k>=kolumna) = False
	| (k==kolumna && w<=(wiersz+d) && w>=wiersz) = False
	| (k==(kolumna+d) && w<=(wiersz+d) && w>=wiersz) = False
	| otherwise = czy_niezawiera xs (wiersz,kolumna,d)


{-

czy_nienachodzi jako argumenty przyjmuje liste kwadratow i kwadrat. Zwraca true wtedy i tylko wtedy, kiedy brzegi kwadratu nie pokrywaja sie z zadnym kwadratem z listy, oraz jego rogi nie stykaja sie z zadnym rogiem kwadratow z listy.

-}

czy_nienachodzi :: Kwadrat -> Kwadrat -> Bool
czy_nienachodzi (w,k,de) (wiersz, kolumna, d)
	| czy_zawiera (w,k,de) (wiersz+d,kolumna) = False
	| czy_zawiera (w,k,de) (wiersz,kolumna+d) = False
	| czy_zawiera (w,k,de) (wiersz+d,kolumna+d) = False
	| czy_zawiera (w,k,de) (wiersz,kolumna) = False
	| czy_zawiera (wiersz, kolumna, d) (w+de,k) = False
	| czy_zawiera (wiersz, kolumna, d) (w,k+de) = False
	| czy_zawiera (wiersz, kolumna, d) (w+de,k+de) = False
	| czy_zawiera (wiersz, kolumna, d) (w,k) = False
	| otherwise = True

{-

czy_zawiera przyjmuje kwadrat oraz punkt. Zwraca true jesli punkt zawiera sie w kwadracie, jest to inna wersja funkcji czy_niezawiera.
-}
	
czy_zawiera :: Kwadrat -> (Int,Int) -> Bool
czy_zawiera (wiersz,kolumna,d) (w, k)
	| (w==wiersz && k<=(kolumna+d) && k>=kolumna) = True
	| (w==(wiersz+d) && k<=(kolumna+d) && k>=kolumna) = True
	| (k==kolumna && w<=(wiersz+d) && w>=wiersz) = True
	| (k==(kolumna+d) && w<=(wiersz+d) && w>=wiersz) = True
	| otherwise = False

	
{-

funkcje generuj tworza wszystkie odpowiednie kwadraty. m jest to maksymalna liczba przejsc tej funkcji (innymi slowy zwracana jest lista liczb powiekszana w odpowiednia strone przez wartosci 1 do m.

-}
	
generuj_gora_lewo :: Int -> Liczba -> [Kwadrat] 
generuj_gora_lewo m (wiersz,kolumna,_) = [(wiersz-a,kolumna-a,a) | a<-[1..m]]

generuj_dol_lewo :: Int -> Liczba -> [Kwadrat] 
generuj_dol_lewo m (wiersz,kolumna,_) = [(wiersz,kolumna-a,a) | a<-[1..m]]

generuj_gora_prawo :: Int -> Liczba -> [Kwadrat] 
generuj_gora_prawo m (wiersz,kolumna,_) = [(wiersz-a,kolumna,a) | a<-[1..m]]
	
generuj_dol_prawo :: Int -> Liczba -> [Kwadrat] 
generuj_dol_prawo m (wiersz,kolumna,_) = [(wiersz,kolumna,a) | a<-[1..m]]