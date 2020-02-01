<?php

namespace src;

use Money\Money;

class Wallet
{
    private $resources;
    private $events;
    private $state;

    public function __construct(Money $initResources, $initState = ["active", ""])
    {
        $this->resources = $initResources;
        $this->state     = $initState;
        $this->events    = [new WalletConstruct($this->resources, $initState)];
    }

    public static function fromEvents(array $events)
    : Wallet
    {
        if ($events[0] == WalletConstruct::class)
        {
            $initResources = $events[0]->getResources();
            $initState     = $events[0]->getState();
            $wallet        = new Wallet($initResources, $initState);

            array_shift($events);

            foreach ($events as $event)
            {
                try
                {
                    switch ($event)
                    {
                        case WalletDeposit::class:
                            $wallet->deposit($event->getValue());
                            break;
                        case WalletWithdraw::class:
                            $wallet->withdraw($event->getValue());
                            break;
                        case WalletActivate::class:
                            $wallet->activate($event->getReason());
                            break;
                        case WalletDeactivate::class:
                            $wallet->deactivate($event->getReason());
                            break;
                        default:
                            throw new \Exception("Wrong Event Sequence");
                    }
                } catch (\Exception $e)
                {
                    throw new \Exception("Wrong Event Sequence!");
                }
            }

            return $wallet;

        } else
        {
            throw new \Exception("Wrong Event Sequence!");
        }
    }

    public function deposit(Money $moneyToDeposit)
    : void
    {
        if ($this->resources->isSameCurrency($moneyToDeposit))
        {
            $this->resources = $this->resources->add($moneyToDeposit);
            $this->events[]  = new WalletDeposit($moneyToDeposit);
        } else
        {
            throw new \Exception("Wrong currency!");
        }
    }

    public function withdraw(Money $moneyToWithdraw)
    : void
    {
        if ($this->resources->isSameCurrency($moneyToWithdraw))
        {

            if ($this->resources->greaterThanOrEqual($moneyToWithdraw))
            {
                $this->resources = $this->resources->subtract($moneyToWithdraw);
                $this->events[]  = new WalletWithdraw($moneyToWithdraw);
            } else
            {
                throw new \Exception("Not enough resources!");
            }
        } else
        {
            throw new \Exception("Wrong currency!");
        }
    }

    public function deactivate(string $reason)
    : void
    {
        if ($this->state[0] == "active")
        {
            $this->state    = ["inactive", $reason];
            $this->events[] = new WalletDeactivate($reason);
        } else
        {
            throw new \Exception("Your Wallet is already inactive!");
        }
    }

    public function activate(string $reason)
    : void
    {
        if ($this->state[0] == "inactive")
        {
            $this->state    = ["active", $reason];
            $this->events[] = new WalletActivate($reason);
        } else
        {
            throw new \Exception("Your Wallet is already inactive!");
        }
    }

    public function getBalance()
    : Money
    {
        if ($this->state[0] == "active")
        {
            return $this->resources;
        } else
        {
            throw new \Exception("Your wallet is inactive!");
        }
    }

    public function getEvents()
    : array
    {
        return $this->events;
    }
}