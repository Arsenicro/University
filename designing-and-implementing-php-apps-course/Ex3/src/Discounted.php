<?php

namespace src;

use Money\Money;

class Discounted implements IProduct
{
    private $product;
    private $discount;

    public function __construct(IProduct $product, int $discount)
    {
        if ($discount > 100 || $discount < 0)
        {
            throw new Exception("Discount should be between 0% and 100% !");
        }

        $this->product  = $product;
        $this->discount = $discount;
    }

    public function getName()
    : string
    {
        return $this->product->getName();
    }

    public function getPrice()
    : Money
    {
        $price = $this->product->getPrice();

        return $price->subtract($price->multiply($this->discount / 100));
    }

    public function getDiscount()
    : int
    {
        return $this->discount;
    }
}