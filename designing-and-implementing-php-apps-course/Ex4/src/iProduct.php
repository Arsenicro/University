<?php

interface iProduct
{

    public function getId();

    public function getName();

    public function getMoney();

    public function editProduct(array $newValues);
}