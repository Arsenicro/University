<?php

namespace src;

interface Promotion
{
    public function canPromote(Cart $cart)
    : bool;
}