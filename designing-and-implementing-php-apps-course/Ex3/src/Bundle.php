<?php

namespace src;

use Money\Money;

class Bundle implements IProduct
{
    private $name;
    private $products;
    private $currency;

    public function __construct(string $name, string $currency = "PLN", IProduct ... $products)
    {
        $this->name     = $name;
        $this->currency = $currency;
        foreach ($products as $product)
        {
            if ($product->getPrice()->getCurrency() != $this->currency)
            {
                throw new Exception("Wrong currency!");
            } else
            {
                $this->products[] = $product;
            }
        }
    }

    public function addProducts(IProduct ... $products)
    {
        foreach ($products as $product)
        {
            if ($product->getPrice()->getCurrency() != $this->currency)
            {
                throw new Exception("Wrong currency!");
            } else
            {
                $this->products[] = $product;
            }
        }
    }

    public function addProduct(IProduct $product)
    {
        if ($product->getPrice()->getCurrency() != $this->currency)
        {
            throw new Exception("Wrong currency!");
        }
        $this->products[] = $product;
    }

    public function getName()
    : string
    {
        return $this->name;
    }

    public function getPrice()
    : Money
    {
        $price = new Money(0, $this->products[0]->getPrice()->getCurrency());

        foreach ($this->products as $product)
        {
            $price = $price->add($product->getPrice());
        }

        return $price;
    }
}