<?php

namespace src;

class CountPromotion implements Promotion
{
    private $count;

    public function __construct(int $count)
    {
        $this->count = $count;
    }

    public function canPromote(Cart $cart)
    : bool
    {
        if ($cart->count() >= $this->count)
        {
            return true;
        } else
        {
            return false;
        }
    }
}