<?php

declare(strict_types=1);

require_once($_SERVER['DOCUMENT_ROOT'] . 'vendor/autoload.php');

use PHPUnit\Framework\TestCase;
use src\Stack;

final class StackClassTest extends TestCase
{
    public function testNewStackIsEmpty()
    : void
    {
        $stack         = new Stack();
        $stackElements = $stack->getStack();

        $this->assertTrue(empty($stackElements));
    }

    public function testEmptyStackIsEmpty()
    : void
    {
        $stack = new Stack();

        $this->assertTrue($stack->isEmpty());
    }

    public function testNotEmptyStackIsNotEmpty()
    : void
    {
        $stack = new Stack(100, [1]);

        $this->assertFalse($stack->isEmpty());
    }

    public function testCanPopElement()
    : void
    {
        $stack = new Stack(100, [1]);

        $element       = $stack->pop();
        $stackElements = $stack->getStack();

        $this->assertTrue(empty($stackElements));
        $this->assertEquals(1, $element);
    }

    public function testCantPopEmptyStack()
    : void
    {
        $this->expectException(Exception::class);

        $stack = new Stack();

        $stack->pop();
    }

    public function testPushingElements()
    : void
    {
        $array = [2, 1, 3, 7, 1, 1, 2, 3, "X", "D", "Lizard", 123, 12345, "OLA"];
        $stack = new Stack();

        foreach ($array as $item)
        {
            $stack->push($item);
        }

        $stackElements = $stack->getStack();
        $stackElements = array_reverse($stackElements);

        $this->assertEquals($array, $stackElements);
    }

    public function testPopingElement()
    : void
    {
        $array = [2, 1, 3, 7, 1, 1, 2, 3, "X", "D", "Lizard", 123, 12345, "OLA"];
        $stack = new Stack(100, $array);

        $elements = [];

        foreach ($array as $item)
        {
            array_push($elements, $stack->pop());
        }

        $this->assertEquals($array, $elements);
    }

    public function testStackIsLimited()
    : void
    {
        $this->expectException(Exception::class);

        $stack = new Stack(1);

        $stack->push("");
        $stack->push("");
    }

    public function testCantPopTooMuch()
    : void
    {
        $this->expectException(Exception::class);

        $array = [2, 1, 3, 7, 1, 1, 2, 3];
        $stack = new Stack(100, $array);

        for ($i = 0; $i < 9; $i++)
        {
            $stack->pop();
        }
    }
}
