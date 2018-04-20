<?php

namespace src;

class WalletDeactivate
{
    private $reason;

    public function __construct($reason)
    {
        $this->reason = $reason;
    }

    public function getReason()
    {
        return $this->reason;
    }
}