# Projektowanie i implementacja zaawansowanych aplikacji PHP

## Money Wallet


### Zadanie


Dana jest klasa `Wallet`, udostępniająca następujące operacje:

- wpłatę środków
- wypłatę środków
- deaktywację konta
- aktywację konta
- sprawdzenie aktualnego salda konta
- możliwość skonstruowania obiektu z przekazanej kolekcji zdarzeń

```php
class Wallet
{
    // ...

    public static function fromEvents(array $events): Wallet
    {
        // ...
    }

    public function deposit(Money $moneyToDeposit): void
    {
        // ...
    }

    public function withdraw(Money $moneyToWithdraw): void
    {
        // ...
    }

    public function deactivate(string $reason): void
    {
        // ..
    }

    public function activate(string $reason): void
    {
        // ..
    }

    public function getBalance(): Money
    {
        // ...
    }
    
    // ...
}
```

Uzupełnij implementację klasy `Wallet` tak, aby:

- każda metoda zmieniająca stan systemu generowała obiekt odpowiedniego zdarzenia
    - zaprojektuj i zaimplementuj obiekty tych zdarzeń
- generowane zdarzenia były rejestrowane wewnątrz obiektu
- operacje niepoprawne, np. wypłata większej ilości środków niż aktualny balans walletu, generowały wyjątki
    - jakie operacje nie powinny być możliwe?
- istniała możliwosć odtworzenia obiektu z przekazanej kolekcji zdarzeń

Przygotuj skrypt demonstracyjny `wallet.php` w katalogu głównym projektu, przyjmujący następujące parametry z linii poleceń:

- nazwę waluty, np. PLN, EUR, GBP, string
- ilość operacji wpłat środków, int
- n liczb przedstawiających wysokość wpłat, int
- 1 liczbę przedstawiającą wysokość wypłaty, int

Skrypt demonstracyjny powinien utworzyć obiekt `Wallet`, wykonać na nim zadane operacje, a następnie na standardowe wyjście wyświetlić aktualne saldo walletu.


### Przykład

Wywołanie programu:

```
php wallet.php PLN 3 10 20 20 5
```

Wynik:

```
45 PLN
```


### Uwagi

Program będzie uruchamiany z lini poleceń.
