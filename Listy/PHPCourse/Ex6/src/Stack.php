<?php

namespace src;

use Exception;

class Stack
{
    private $stack;
    private $limit;

    public function __construct($limit = 100, $stack = [])
    {
        $this->stack = $stack;
        $this->limit = $limit;
    }

    public function getStack()
    {
        return $this->stack;
    }

    public function push($item)
    {
        if (count($this->stack) < $this->limit)
        {
            array_unshift($this->stack, $item);
        } else
        {
            throw new Exception('Stack is full!');
        }
    }

    public function pop()
    {
        if ($this->isEmpty())
        {
            throw new Exception('Stack is empty!');
        } else
        {
            return array_shift($this->stack);
        }
    }

    public function isEmpty()
    {
        return empty($this->stack);
    }
}