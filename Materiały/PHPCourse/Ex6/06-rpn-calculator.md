# Projektowanie i implementacja zaawansowanych aplikacji PHP

## Kalkulator Odwrotnej Notacji Polskiej


### Zadanie

Odwrotna Notacja Polska jest sposóbem zapisu wyrażeń arytmetycznych, w którym znak opisujący wykonywaną operację umieszczony jest dopiero po operandach. Przykładowo, poniższe wyrażenie

```
(10 + 20) * 3
```

w zapisie ONP przedstawia się następująco:

```
10 20 + 3 *
``` 

Wyrażenia zapisane w ONP obliczane są według następującego algorytmu:

- Dla wszystkich symboli z wyrażenia ONP wykonuj:
    - jeśli i-ty symbol jest liczbą, to odłóż go na stos,
    - jeśli i-ty symbol jest operatorem to:
        - zdejmij ze stosu jeden element (ozn. a),
        - zdejmij ze stosu kolejny element (ozn. b),
        - odłóż na stos wartość b operator a.
    - jeśli i-ty symbol jest funkcją to:
        - zdejmij ze stosu oczekiwaną liczbę parametrów funkcji(ozn. a1...an)
        - odłóż na stos wynik funkcji dla parametrów a1...an
- Zdejmij ze stosu wynik.

Zaimplementuj klasy `RPNCalculator` oraz `Stack`, reprezentujące odpowiednio kalkulator ONP oraz strukturę stosu. Przygotuj uprzednio właściwe testy jednostkowe dla publicznych interfejsów obu klas. Przygotuj skrypt `rpn-calculator.php`, który na wypisze na standardowe wyjście wartość wyrażenia ONP podanego jako argument wywołania programu.

Pamiętaj, aby:

- pliki źródłowe znajdowały się w katalogu `src/`
- pliki testów znajdowały się w katalogu `tests/`
- poprawnie używać Composera oraz namespace'ów


### Przykład

Wywołanie programu:

```
php rpn-calculator.php "2 3 + 5 * 10 +"
35
```


### Uwagi

Program będzie uruchamiany z lini poleceń.


### Wskazówki

Więcej o zapisie Odwrotnej Notacji Polskiej można znaleźć [tutaj](https://pl.wikipedia.org/wiki/Odwrotna_notacja_polska).