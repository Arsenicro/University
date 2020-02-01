<?php

require 'vendor/autoload.php';

use src\Cart;
use src\ManyPromotions;
use src\PricePromotion;
use src\CountPromotion;
use src\ProductPromotion;
use src\ComplicatePromotion;
use src\StandardProduct;
use Money\
{
    Currency, Money
};

$pricePromotion      = new PricePromotion(3000);
$countPromotion      = new CountPromotion(7);
$complicatePromotion = new ComplicatePromotion(new PricePromotion(1400), new CountPromotion(5));
$productPromotion    = new ProductPromotion("TELEWIZOR");

$promotion = new ManyPromotions($pricePromotion,$countPromotion,$complicatePromotion,$productPromotion);

$cart1 = new Cart();
$cart2 = new Cart();
$cart3 = new Cart();
$cart4 = new Cart();
$cart5 = new Cart();

$product1      = new StandardProduct("TELEWIZOR", new Money(900, new Currency("PLN")));
$product2      = new StandardProduct("Produkt2", new Money(500, new Currency("PLN")));
$product3      = new StandardProduct("Produkt3", new Money(200, new Currency("PLN")));
$product4      = new StandardProduct("Produkt4", new Money(200, new Currency("PLN")));
$product5      = new StandardProduct("Produkt5", new Money(200, new Currency("PLN")));
$product6      = new StandardProduct("Produkt6", new Money(400, new Currency("PLN")));
$cheapProduct1 = new StandardProduct("cheapProduct1", new Money(10, new Currency("PLN")));
$cheapProduct2 = new StandardProduct("cheapProduct2", new Money(10, new Currency("PLN")));
$cheapProduct3 = new StandardProduct("cheapProduct3", new Money(10, new Currency("PLN")));
$cheapProduct4 = new StandardProduct("cheapProduct4", new Money(10, new Currency("PLN")));
$cheapProduct5 = new StandardProduct("cheapProduct5", new Money(10, new Currency("PLN")));
$cheapProduct6 = new StandardProduct("cheapProduct6", new Money(10, new Currency("PLN")));
$cheapProduct7 = new StandardProduct("cheapProduct7", new Money(10, new Currency("PLN")));

$cart1->addProduct($cheapProduct1);
$cart1->addProduct($cheapProduct2);
$cart1->addProduct($cheapProduct3);
$cart1->addProduct($cheapProduct4);
$cart1->addProduct($cheapProduct5);
$cart1->addProduct($cheapProduct6);
$cart1->addProduct($cheapProduct7);

$cart2->addProduct($cheapProduct1);
$cart2->addProduct($cheapProduct2);
$cart2->addProduct($cheapProduct3);
$cart2->addProduct($cheapProduct4);
$cart2->addProduct($cheapProduct5);
$cart2->addProduct($cheapProduct6);

$cart3->addProduct($cheapProduct1);
$cart3->addProduct($cheapProduct2);
$cart3->addProduct($cheapProduct3);
$cart3->addProduct($cheapProduct4);
$cart3->addProduct($cheapProduct5);
$cart3->addProduct($cheapProduct6);
$cart3->addProduct($product1);

$cart4->addProduct($product2);
$cart4->addProduct($product3);
$cart4->addProduct($product4);
$cart4->addProduct($product5);

$cart5->addProduct($product2);
$cart5->addProduct($product3);
$cart5->addProduct($product4);
$cart5->addProduct($product5);
$cart5->addProduct($product6);

if ($promotion->canPromote($cart5))
{
    echo "TAK";
} else
{
    echo "NIE";
}