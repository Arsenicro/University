<?php

namespace src;

use Exception;

class SimpleCalculator implements iCalc
{
    public function calculate($number1, $number2, string $operator)
    {
        switch ($operator){
            case "+":
                return $number1 + $number2;
                break;
            case "-":
                return $number1 - $number2;
                break;
            case "*":
                return $number1 * $number2;
                break;
            case "/":
                if($number2 == 0)
                {
                    throw new Exception("You can't dive by 0!");
                }
                return $number1 / $number2;
                break;
            default:
                throw new Exception('Wrong operator!');
        }
    }
}