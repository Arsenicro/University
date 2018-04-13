<?php

declare(strict_types=1);

require_once($_SERVER['DOCUMENT_ROOT'] . 'vendor/autoload.php');

use PHPUnit\Framework\TestCase;
use src\RPNCalculator;
use src\SimpleCalculator;
use src\Stack;

final class testRPNClassTest extends TestCase
{
    private function getStackMock($methods)
    {
        return $stack = $this->getMockBuilder(Stack::class)->setMethods($methods)->getMock();
    }

    private function getCalculatorMock($methods)
    {
        return $this->getMockBuilder(SimpleCalculator::class)->setMethods($methods)->getMock();
    }

    public function testSimpleExpression()
    : void
    {
        $calc  = $this->getCalculatorMock(['calculate']);
        $stack = $this->getStackMock(['push', 'pop']);

        $calc->expects($this->once())->method('calculate')->willReturn(5);
        $stack->expects($this->exactly(3))->method('push');
        $stack->expects($this->exactly(3))->method('pop')->willReturn(3, 2, 5);

        $rpn   = new RPNCalculator($stack, $calc);
        $value = $rpn->calculate("2 3 +");

        $this->assertEquals(5, $value);
    }

    public function testSimpleExpressionWithGoodParameters()
    : void
    {
        $calc  = $this->getCalculatorMock(['calculate']);
        $stack = $this->getStackMock(['push', 'pop']);

        $calc->expects($this->once())->method('calculate')
             ->with(2, 3, "+")
             ->willReturn(5);

        $stack->expects($this->exactly(3))->method('push');
        $stack->expects($this->exactly(3))->method('pop')->willReturn(3, 2, 5);

        $rpn   = new RPNCalculator($stack, $calc);
        $value = $rpn->calculate("2 3 +");

        $this->assertEquals(5, $value);
    }

    public function testSimpleExpressionWithoutGoodParameters()
    {
        $this->expectException(Exception::class);

        $calc  = $this->getCalculatorMock(['calculate']);
        $stack = $this->getStackMock(['push', 'pop']);

        $calc->expects($this->once())->method('calculate')
             ->with(2, 3, "Lizard")
             ->willThrowException(new Exception);
        $stack->expects($this->exactly(2))->method('push')->with($this->logicalOr(2, 3));
        $stack->expects($this->exactly(2))->method('pop')->willReturn(3, 2);

        $rpn = new RPNCalculator($stack, $calc);
        $rpn->calculate("2 3 Lizard");
    }

    public function testMoreComplicatedExpression()
    {
        $calc  = $this->getCalculatorMock(['calculate']);
        $stack = $this->getStackMock(['push', 'pop']);

        $map = [
            [3, 4, "*", 12],
            [10, 5, "/", 2],
            [12, 2, "+", 14],
            [2, 4, "*", 28],
            [28, 12, "+", 40]
        ];

        $calc->expects($this->exactly(5))->method('calculate')->will($this->returnValueMap($map));
        $stack->expects($this->exactly(11))->method('push');
        $stack->expects($this->exactly(11))->method('pop')->willReturn(4, 3, 5, 10, 2, 12, 4, 2, 12, 28, 40);

        $rpn   = new RPNCalculator($stack, $calc);
        $value = $rpn->calculate("12 2 3 4 * 10 5 / + * +");

        $this->assertEquals(40, $value);
    }
}