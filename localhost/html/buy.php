<?php

    // configuration
    require("../includes/config.php");
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check whether a symbol is provided by user
        if (!empty($_POST["symbol"]) && !empty($_POST["shares"]))
        {
            // make sure that users can only buy whole shares of stocks, not fractions           
            if (preg_match("/^\d+$/", $_POST["shares"]))
            {                        
                $stock = lookup($_POST["symbol"]);
                
                // make sure the symbol entered is valid
                if ($stock !== false)
                {
                    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
                    
                    // makes sure user has enough money to buy the required shares
                    if ($cash[0]["cash"] - ($_POST["shares"] * $stock["price"]) < 0)
                    {
                        apologize("You can't afford that.");
                    }
                    
                    // capitalizes symbol
                    $symbol = strtoupper ($_POST["symbol"]);
                    
                    // insert into portfolios table            
                    query("INSERT INTO portfolios (id, symbol, shares) VALUES({$_SESSION["id"]}, 
                         '$symbol', {$_POST["shares"]}) ON DUPLICATE KEY UPDATE shares = shares + 
                         VALUES(shares)");
                    
                    // update users cash         
                    query("UPDATE users SET cash = (cash - {$_POST["shares"]} * {$stock["price"]}) 
                         WHERE id = {$_SESSION["id"]}");
                         
                    // update history table
                    query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES({$_SESSION["id"]}, 
                         'BUY', '$symbol', {$_POST["shares"]},{$stock["price"]})");
                    
                    redirect("/");
                }
                else
                {
                    apologize("Symbol not found.");
                }
            }
            else
            {
                apologize("Invalid number of shares.");
            } 
        }
        else if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
    }
    else
    {
        // render sell_form
        render("buy_form.php", ["title" => "Buy"]);
    }

?>
