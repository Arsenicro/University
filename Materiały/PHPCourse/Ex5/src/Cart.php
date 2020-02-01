<?php

namespace src;

use Countable;
use Money\
{
    Currency, Money
};

class Cart implements Countable
{
    private $products;

    public function __construct()
    {
        $this->products = [];
    }

    public function addProduct(Product $product)
    {
        array_push($this->products, $product);
    }

    public function getTotalPrice()
    : Money
    {
        if ($this->count() == 0)
        {
            return new Money(0, new Currency("PLN"));
        }

        $price = new Money(0, $this->products[0]->getPrice()->getCurrency());

        foreach ($this->products as $product)
        {
            $price = $price->add($product->getPrice());
        }

        return $price;
    }

    public function productList()
    {
        return $this->products;
    }

    public function count()
    {
        return count($this->products);
    }
}