<?php

namespace src;

class ProductPromotion implements Promotion
{
    private $product;

    public function __construct(string $product)
    {
        $this->product = $product;
    }

    public function canPromote(Cart $cart)
    : bool
    {
        foreach ($cart->productList() as $product)
        {
            if ($product->getName() == $this->product)
            {
                return true;
            }
        }

        return false;
    }
}