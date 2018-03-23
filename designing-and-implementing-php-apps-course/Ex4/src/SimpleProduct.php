<?php

use Money\Currency;
use Money\Money;

class SimpleProduct implements iProduct, \JsonSerializable
{
    private $id;
    private $name;
    private $money;

    public function __construct(int $id, string $name, Money $money)
    {
        $this->id    = $id;
        $this->name  = $name;
        $this->money = $money;
    }

    public function getId()
    : int
    {
        return $this->id;
    }

    public function getName()
    : string
    {
        return $this->name;
    }

    public function getMoney()
    : Money
    {
        return $this->money;
    }

    public function jsonSerialize()
    {
        return get_object_vars($this);
    }

    public function editProduct(array $newValues)
    {
        $this->name = $newValues["name"] ?? $this->name;
        $amount     = $newValues["amount"] ?? $this->money->getAmount();
        $currency   = $newValues["currency"] ?? $this->money->getCurrency()->getCode();

        $this->money = new Money($amount, new Currency($currency));
    }
}