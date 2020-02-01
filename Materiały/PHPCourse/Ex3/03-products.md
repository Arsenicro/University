# Projektowanie i implementacja zaawansowanych aplikacji PHP

## Produkty


### Zadanie

Interfejs IProduct jest zdefiniowany następująco:

```php
interface IProduct
{
    public function getName(): string;
    
    public function getPrice(): Money;
}
```

gdzie Money jest typem zaimplementowanym w bibliotece [Money](https://github.com/moneyphp/money).

Zaprojektuj, a następnie korzystając z powyższego interfejsu zaimplementuj następujące klasy:

- Product, stanowiącą podstawową implementację interfejsu IProduct
- Bundle, reprezentującą zestawu dowolnych produktów
    - cena zestawu to suma cen znajdujących się w nich produktów
    - zestaw ma swoją nazwę, niezależną od nazw produktów wchodzących w jego skład
- Discounted, reprezentującą dowolny produkt przeceniony o x%

Zgodnie ze rekomendacją [PSR-4 Autoloader](https://www.php-fig.org/psr/psr-4/), umieść klasy w odpowiednich podkatalogach `src/`.

Przygotuj skrypt `demo.php` w katalogu głównym projektu, demonstrujący możliwości twojego rozwiązania, którego częścią będzie poniższa pętla. Skorzystaj z biblioteki Money do reprezentacji pieniędzy.


```php
require 'vendor/autoload.php';

...

$product1 = new Product("produkt 1", Money::PLN(10000));
$product2 = new Product("produkt 2", Money::PLN(10000));
$totalPrice = Money::PLN(0);


$products = [
    $product1,
    $product2,
    // ... w tym miejscu powinny się znaleźć także zestawy produktów i produkty przecenione
];

foreach ($products as $product) {
    echo $product->getName() . PHP_EOL;
    
    $totalPrice = $totalPrice->add($product->getPrice());
}

echo 'TOTAL PRICE: ...'; // wyświetl łączną cenę wszystkich produktów
```


### Uwagi

Program będzie uruchamiany z lini poleceń. 


### Wskazówki

- Bibliotekę Money można zainstalować poleceniem `composer require moneyphp/money`
- Instalacja comosera jest dostępna pod adresem https://getcomposer.org/download/