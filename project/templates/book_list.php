<ul class="nav nav-pills">
    <li><a href="search.php"><strong>Search Ebooks</strong></a></li>
    <li><a href="password.php"><strong>Change Password</strong></a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<form action="index.php" method="post">

    <table class="table table-striped">
        <thead>
            <tr>
                <th>Ebook Name</th>
                <th>Author</th>
                <th>Course</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($books as $book): ?>
            <tr>
                <td><?= $book["name"] ?></td>
                <td><?= $book["author"] ?></td>
                <td><?= $book["course"] ?></td>
                <td><?= '<input type="checkbox" name="'.$book["book_id"].'" value="insert">' ?>
            </tr>
            <? endforeach ?>
       </tbody>
    </table>

    <button class="btn btn-primary" type="submit">Add to My Books</button>
    
</form>
