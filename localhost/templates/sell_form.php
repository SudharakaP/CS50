<form action="sell.php" method="post">
    <fieldset>
        <div class="control-group">
            <select name="symbol">
                <option value=''></option>
                
                <?php foreach ($rows as $row): ?>
                
                    <?= "<option value='{$row["symbol"]}'> {$row["symbol"]} </option>" ?>
                                    
                <? endforeach ?>
                
            </select>
        </div>
        <div class="control-group">
            <button type="submit" class="btn">Sell</button>
        </div>
    </fieldset>
</form>
<div>
    Click <a href="index.php">here</a> to return to portfolio.
</div>
