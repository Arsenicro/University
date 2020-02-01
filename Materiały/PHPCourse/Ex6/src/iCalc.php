<?php

namespace src;

interface iCalc
{
    public function calculate($number1, $number2, string $operator);
}