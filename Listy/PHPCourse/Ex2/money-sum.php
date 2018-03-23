<?php

class Money
{
    private $fractionalPart;
    private $totalPart;
    private $penny;
    private $currency;
    private $precision;

    function __construct(float $amo, string $curr)
    {
        if ($amo < 0)
        {
            return new Exception("Amount should be positive float!");
        }

        $this->penny          = $this->howManyPennies($curr);
        $this->precision      = intval(floor(log10($this->penny - 1)) + 1);
        $this->totalPart      = intval(round(floor($amo)));
        $this->fractionalPart = intval(round(fmod($amo, 1) * 10 ** $this->precision));
        $this->currency       = $curr;
    }

    public function getAmount()
    {
        $frac = $this->fractionalPart / (10 ** $this->precision);

        return $this->totalPart + $frac;
    }

    public function getCurrency()
    {
        return $this->currency;
    }

    public function getTotalPart()
    {
        return $this->totalPart;
    }

    public function getFractionPart()
    {
        return $this->fractionalPart;
    }

    private function howManyPennies(string $currency)
    {
        if ($currency == "PESOS")
        {
            return 60;
        }

        return 100;
    }

    private function normalize()
    {
        while ($this->fractionalPart < 0)
        {
            $this->totalPart      -= 1;
            $this->fractionalPart += $this->penny;
        }

        while ($this->fractionalPart / $this->penny >= 1)
        {
            $this->totalPart      += 1;
            $this->fractionalPart -= $this->penny;
        }
    }

    public function add(Money $money)
    {
        if ($this->currency !== $money->getCurrency())
        {
            return new Exception("Wrong currency!");
        }

        $this->fractionalPart += $money->getFractionPart();
        $this->totalPart      += $money->getTotalPart();

        $this->normalize();

        return true;
    }

    public function sub(Money $money)
    {
        if ($this->currency !== $money->getCurrency())
        {
            return new Exception("Wrong currency!");
        }

        $amount = $this->getAmount() - $money->getAmount();

        if ($amount < 0)
        {
            return new Exception("You are bankrupt!");
        }

        $this->fractionalPart -= $money->getFractionPart();
        $this->totalPart      -= $money->getTotalPart();

        $this->normalize();

        return true;
    }

    public function mult(int $number)
    {
        $this->fractionalPart *= $number;
        $this->totalPart      *= $number;

        $this->normalize();

        return true;
    }

    public function div(int $number)
    {
        if ($number == 0)
        {
            return new Exception("You cant dive by 0!");
        }

        $this->fractionalPart /= $number;
        $this->totalPart      /= $number;

        $this->normalize();

        return true;
    }
}

interface moneyFormatter
{
    public function toString();
}

class simpleFormatter implements moneyFormatter
{
    private $amount;
    private $total;
    private $fractional;
    private $currency;

    public function __construct(Money $money)
    {
        $this->amount     = $money->getAmount();
        $this->currency   = $money->getCurrency();
        $this->total      = strval($money->getTotalPart());
        $this->fractional = strval($money->getFractionPart());
    }

    public function toString()
    {
        $returningString = "";
        $total           = $this->total;
        $frac            = $this->fractional;
        $currency        = $this->currency;
        $leng            = strlen($total);

        for ($i = 0; $i < $leng; $i++)
        {
            $returningString .= $total[$i];

            if (($leng - $i - 1) % 3 == 0 && $i < $leng - 1)
            {
                $returningString .= " ";
            }
        }

        $returningString .= ",";
        $returningString .= $frac;
        $returningString .= " " . $currency;

        return $returningString;
    }
}

$currency = $argv[1];

$money = new Money(0, $currency);

foreach ($argv as $i => $amount)
{
    if ($i > 1)
    {
        $newMoney = new Money($amount, $currency);
        $money->add($newMoney);
    }
}

$formatter = new simpleFormatter($money);
echo $formatter->toString();