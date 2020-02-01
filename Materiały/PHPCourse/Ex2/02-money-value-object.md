# Projektowanie i implementacja zaawansowanych aplikacji PHP

## Money Value Object


### Zadanie

Zaprojektuj, a następnie zaimplementuj klasę Money, reprezentującą wartość pieniężną (kwota + waluta). Klasa ta powinna umożliwiać następujące operacje:

- dodanie innego obiektu klasy Money (5.00 PLN + 10.00 PLN)
- odjęcie innego obiektu klasy Money (10.00 PLN - 10.00 PLN)
- przemnożenie przez liczbę (5.00 PLN * 2)
- podzielenie przez liczbę  (10.60 PLN / 2)

W przypadku braku możliwości wykonania operacji, np. operowania na różnych walutach, wygeneruj odpowiedni wyjątek.

Zaprojektuj, a następnie zaimplementuj:

- interfejs MoneyFormatter, przeznaczony do formatowania obiektu Money do wartości typu string
- klasę formattera, pozwalającego na podanie separatora tysięcy oraz znaku przecinka dziesiętnego, implementującą interfejs MoneyFormatter

Korzystając z przygotowanych klas, napisz program, który zsumuje kwoty, przekazane jako parametry wywołania skryptu, a następnie wyświetli sformatowaną wartość końcową.


### Przykład

Wywołanie programu:

```
php money-sum.php PLN 1000.00 2.00 3.50 1000000.00
```

Wynik:

```
1 001 005,50 PLN
```


### Uwagi

Program będzie uruchamiany z lini poleceń. 
