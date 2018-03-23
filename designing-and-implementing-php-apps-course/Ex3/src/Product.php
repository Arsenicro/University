<?php

namespace src;

use Money\Money;

class Product implements IProduct
{
    private $name;
    private $price;

    public static function Product(string $name, Money $price)
    {
        return new Product($name, $price);
    }

    public function __construct(string $name, Money $price)
    {
        $this->name  = $name;
        $this->price = $price;
    }

    public function getName()
    : string
    {
        return $this->name;
    }

    public function getPrice()
    : Money
    {
        return $this->price;
    }
}