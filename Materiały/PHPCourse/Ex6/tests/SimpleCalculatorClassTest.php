<?php
declare(strict_types=1);

require_once($_SERVER['DOCUMENT_ROOT'] . 'vendor/autoload.php');

use PHPUnit\Framework\TestCase;
use src\SimpleCalculator;

final class SimpleCalculatorClassTest extends TestCase
{
    public function testCanAddTwoNumbers() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(10, $simpleCalc->calculate(5, 5, "+"));
    }

    public function testCanAddZero() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(12, $simpleCalc->calculate(12, 0, "+"));
    }

    public function testCanSubTwoNumbers() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(10, $simpleCalc->calculate(15, 5, "-"));
    }

    public function testCanSubZero() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(15, $simpleCalc->calculate(15, 0, "-"));
    }

    public function testCanMultiplyTwoNumbers() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(25, $simpleCalc->calculate(5, 5, "*"));
    }

    public function testCanMultiplyByZero() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(0, $simpleCalc->calculate(5, 0, "*"));
    }

    public function testCanDivTwoNumbers() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->assertEquals(5, $simpleCalc->calculate(10, 2, "/"));
    }

    public function testCantDivBy0() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->expectException(Exception::class);

        $simpleCalc->calculate(10, 0, "/");
    }

    public function testCantLizardNumbers() : void
    {
        $simpleCalc = new SimpleCalculator();

        $this->expectException(Exception::class);

        $simpleCalc->calculate(10, 4, "Lizard");
    }
}