<?php

namespace src;

use Money\Money;

class WalletConstruct
{
    private $resources;
    private $state;

    public function __construct($resources, $state = ["active", ""])
    {
        $this->resources = $resources;
        $this->state     = $state;
    }

    public function getResources() : Money
    {
        return $this->resources;
    }

    public function getState()
    {
        return $this->state;
    }

}