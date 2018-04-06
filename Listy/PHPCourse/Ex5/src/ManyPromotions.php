<?php

namespace src;

class ManyPromotions implements Promotion
{
    private $promotions;

    public function __construct(Promotion ... $promotions)
    {
        $this->promotions = $promotions;
    }

    public function canPromote(Cart $cart)
    : bool
    {
        $or = false;

        foreach ($this->promotions as $promotion)
        {
            $or |= $promotion->canPromote($cart);
        }

        return $or;
    }
}