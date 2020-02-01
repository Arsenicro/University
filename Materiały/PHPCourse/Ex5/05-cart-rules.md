# Projektowanie i implementacja zaawansowanych aplikacji PHP

## Cart Rules


### Zadanie

Dany jest interfejs `Product` oraz jego podstawowa implementacja `StandardProduct`:

```php
interface Product
{
    public function getName(): string;
    
    public function getPrice(): Money;
}
 
class StandardProduct implements Product
{
    // ...
}
```

Dana jest klasa `Cart`, przedstawiająca koszyk przykładowej aplikacji ecommerce<sup>1</sup>:

```php
class Cart implements Countable
{
   
    public function addProduct(Product $product)
    {
        // ...
    }
    
    // Zwraca łączną sumę dodanych do koszyka produktów
    public function getTotalPrice(): Money
    {
        // ...
    }
    
    // ...
}
```

Wykorzystując powyższe definicje zaprojektuj, a następnie zaimplementuj mechanizm pozwalający dodać do koszyka dodatkowy produkt (np. gift), jeśli koszyk spełnia określone kryteria. Przygotuj implementacje dla następujących kryteriów:

- Jeśli koszyk zawiera więcej niż X produktów, koszyk kwalifikuje się do promocji
- Jeśli łączna kwota produktów w koszyka jest większa niż X, koszyk kwalifikuje się do promocji
- Jeśli koszyk zawiera produkt zawierający w nazwie 'TELEWIZOR', koszyk kwalifikuje się do promocji
- Jeśli koszyk zawiera więcej niż X produktów i łączna kwota produktów w koszyku jest większa niż Y, koszyk kwalifikuje się do promocji 

Przygotuj skrypt `cart.php`, w którym:

- zbudowany zostanie przykładowy koszyk
- zbudowana zostanie tablica kryteriów promocji
- koszyk zostanie sprawdzony pod kątem zdefiniowanych kryteriów
- na standardowe wyjście zostanie wyświetlony ciąg znaków `TAK`, jeśli koszyk spełnia choć jedno z podanych kryteriów, lub `NIE` w przeciwnym wypadku

Rozwiązanie powinno być zgodne z regułami SOLID oraz pozwalać na bardzo proste rozszerzenie systemu o kolejne kryteria. Zadbaj o odpowiednie nazewnictwo oraz rozłożonie klas/interfejsów pomiędzy namespace'y i katalogi.


#### Przypisy 

<sup>1</sup>W tym wypadku klasa `Cart` ma zbyt dużo odpowiedzialności, jednak dla uproszczenia zadania możemy się na to zgodzić. Uproszczenie polega w tym wypadku na przechowywaniu w obiekcie klasy `Cart` instancji `Product` (zamiast jedynie informacji o ich identyfikatorach) oraz na umieszczenie w niej metody `getTotalPrice()` (zamiast w osobnym serwisie).


### Uwagi

Program będzie uruchamiany z lini poleceń. 


## Wskazówki

Interfejs [Countable](http://php.net/manual/en/class.countable.php) jest wbudowany w język, nie potrzeba go definiować samodzielnie. 