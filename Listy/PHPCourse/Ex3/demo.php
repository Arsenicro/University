<?php

require 'vendor/autoload.php';

use Money\Money;
use src\Bundle;
use src\Product;
use src\Discounted;

$productBundle1 = new Bundle("Zestaw1", "PLN");
$productBundle1->addProduct(Product::Product('Produkt1', Money::PLN(400)));
$productBundle1->addProduct(Product::Product('Produkt2', Money::PLN(670)));
$productBundle1->addProduct(Product::Product('Produkt3', Money::PLN(330)));
$productBundle1->addProduct(Product::Product('Produkt4', Money::PLN(440)));
$productBundle1->addProduct(Product::Product('Produkt5', Money::PLN(260)));

$productBundle2 = new Bundle("Zestaw2");
$productBundle2->addProduct(Product::Product('Produkt1', Money::PLN(1200)));
$productBundle2->addProduct(Product::Product('Produkt2', Money::PLN(1400)));
$productBundle2->addProduct(Product::Product('Produkt3', Money::PLN(1400)));
$productBundle2->addProduct(Product::Product('Produkt4', Money::PLN(1440)));
$productBundle2->addProduct(Product::Product('Produkt5', Money::PLN(1560)));

$discountedProduct1 = new Discounted(Product::Product("Przeceniony1", Money::PLN(1000)), 10);
$discountedProduct2 = new Discounted(Product::Product("Przeceniony2", Money::PLN(1000)), 15);
$discountedProduct3 = new Discounted(Product::Product("Przeceniony3", Money::PLN(1000)), 23);

$product1   = new Product("produkt 1", Money::PLN(10000));
$product2   = new Product("produkt 2", Money::PLN(10000));
$totalPrice = Money::PLN(0);


$products = [
    $product1,
    $product2,
    $productBundle1,
    $productBundle2,
    $discountedProduct1,
    $discountedProduct2,
    $discountedProduct3
];

foreach ($products as $product)
{
    echo $product->getName() . PHP_EOL;
    echo $product->getPrice()->getAmount() . PHP_EOL;

    $totalPrice = $totalPrice->add($product->getPrice());
}

echo 'TOTAL PRICE: ' . $totalPrice->getAmount() . PHP_EOL;

$maximumBundle = new Bundle('Maximum!', "PLN", $product1, $product2, $productBundle1, $productBundle2);
$maximumBundle->addProducts($discountedProduct1, $discountedProduct2, $discountedProduct3);

echo "MaximumBundle: " . $maximumBundle->getPrice()->getAmount() . PHP_EOL;

$discountedBundle = new Discounted($maximumBundle, 20);
echo "Discount!: " . $discountedBundle->getPrice()->getAmount() . PHP_EOL;
