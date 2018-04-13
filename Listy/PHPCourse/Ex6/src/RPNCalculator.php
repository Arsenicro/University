<?php

namespace src;

use Exception;

class RPNCalculator
{
    private $stack;
    private $calculator;

    public function __construct(Stack $stack = null, iCalc $calculator = null)
    {
        $this->stack      = $stack      ?? new Stack();
        $this->calculator = $calculator ?? new SimpleCalculator();
    }

    public function calculate(string $formula)
    {
        $elements = explode(" ", $formula);

        foreach ($elements as $element)
        {
            if (is_numeric($element))
            {
                $this->stack->push((int)$element);
            } else
            {
                try
                {
                    $number2 = $this->stack->pop();
                    $number1 = $this->stack->pop();
                } catch (Exception $e)
                {
                    throw new Exception("Not enough numbers!");
                }
                try
                {
                    $value = $this->calculator->calculate($number1, $number2, $element);
                    $this->stack->push($value);
                } catch (Exception $e)
                {
                    throw new Exception("Wrong formula!");
                }
            }
        }
        try
        {
            $number = $this->stack->pop();
        } catch (Exception $e)
        {
            throw new Exception("Wrong formula!");
        }

        if ($this->stack->isEmpty())
        {
            return $number;
        } else
        {
            throw new Exception("Not enough operators!");
        }
    }
}