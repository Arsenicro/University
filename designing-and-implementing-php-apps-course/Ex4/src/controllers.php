<?php

use Money\Currency;
use Money\Money;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;

$app->get('/', function () use ($app)
{
    return $app['twig']->render('index.html.twig', array());
})
    ->bind('homepage');

$app->get('/products', function (Request $request) use ($app)
{
    try
    {
        $storage  = $app['storage'];
        $products = $storage->getAll();
    } catch (Exception $e)
    {
        return new Response('Something wen\'t wrong!');
    }

    return json_encode($products);
});

$app->post('/products', function (Request $request) use ($app)
{
    $id       = (int)$request->get('id');
    $name     = $request->get('name');
    $amount   = (int)$request->get('amount');
    $currency = $request->get('currency');


    try
    {
        $money = new Money($amount, new Currency($currency));
        $product = new SimpleProduct($id, $name, $money);
        $storage = $app['storage'];
        $storage->save($product);
    } catch (Exception $e)
    {
        return new Response('Something wen\'t wrong!');
    }

    return new Response('Added!', 201);
});

$app->get('/products/{id}', function ($id) use ($app)
{
    try
    {
        $storage = $app['storage'];
        $product = $storage->load($id);
    } catch (Exception $e)
    {
        return new Response('Something wen\'t wrong!');
    }

    return json_encode($product);

});

$app->put('/products/{id}', function (Request $request, $id) use ($app)
{
    $newValues = [];

    if ($request->get('name') != null)
    {
        $newValues['name'] = $request->get('name');
    }
    if ($request->get('amount') != null)
    {
        $newValues['amount'] = $request->get('amount');
    }
    if ($request->get('currency') != null)
    {
        $newValues['currency'] = $request->get('currency');
    }

    try
    {
        $storage = $app['storage'];
        $storage->edit($id, $newValues);
    } catch (Exception $e)
    {
        return new Response('Something wen\'t wrong!');
    }


    return new Response('Changed!', 201);
});

$app->delete('/products/{id}', function ($id) use ($app)
{
    try
    {
        $storage = $app['storage'];
        $storage->delete($id);
    } catch (Exception $e)
    {
        return new Response('Something wen\'t wrong!');
    }

    return new Response('Deleted!', 201);
});

$app->error(function (\Exception $e, Request $request, $code) use ($app)
{
    if ($app['debug'])
    {
        return;
    }

    // 404.html, or 40x.html, or 4xx.html, or error.html
    $templates = array(
        'errors/' . $code . '.html.twig',
        'errors/' . substr($code, 0, 2) . 'x.html.twig',
        'errors/' . substr($code, 0, 1) . 'xx.html.twig',
        'errors/default.html.twig',
    );

    return new Response($app['twig']->resolveTemplate($templates)->render(array('code' => $code)), $code);
});
