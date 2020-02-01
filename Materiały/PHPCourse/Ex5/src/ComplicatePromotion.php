<?php

namespace src;

class ComplicatePromotion implements Promotion
{
    private $promotions;

    public function __construct(Promotion ... $promotions)
    {
        $this->promotions = $promotions;
    }

    public function canPromote(Cart $cart)
    : bool
    {
        $and = true;

        foreach ($this->promotions as $promotion)
        {
            $and &= $promotion->canPromote($cart);
        }

        return $and;
    }
}