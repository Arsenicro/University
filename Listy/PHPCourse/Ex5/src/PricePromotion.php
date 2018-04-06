<?php

namespace src;

class PricePromotion implements Promotion
{
    private $price;

    public function __construct(int $price)
    {
        $this->price = $price;
    }

    public function canPromote(Cart $cart)
    : bool
    {
        if ($cart->getTotalPrice()->getAmount() > $this->price)
        {
            return true;
        } else
        {
            return false;
        }
    }
}