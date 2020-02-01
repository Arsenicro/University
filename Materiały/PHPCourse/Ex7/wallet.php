<?php
require 'vendor/autoload.php';
use src\Wallet;

$curr             = $argv[1];
$numberOfDeposits = $argv[2];

$operations  = array_slice($argv, 3);
$withdrawOperations = array_slice($argv, $numberOfDeposits + 1);
$currency = new \Money\Currency($curr);
$wallet = new Wallet(new \Money\Money(0,$currency));

for ($i = 0; $i < $numberOfDeposits; $i++)
{
    $wallet->deposit(new \Money\Money($operations[$i],$currency));
}

$wallet->withdraw(new \Money\Money($operations[$numberOfDeposits],$currency));

echo $wallet->getBalance()->getAmount() . " " . $wallet->getBalance()->getCurrency() . PHP_EOL;