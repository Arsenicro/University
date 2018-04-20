<?php

namespace src;

class WalletActivate
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