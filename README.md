<h1>Minesweeper Game</h1>
<p>This is a console-based implementation of the classic Minesweeper game in C++. The game initializes a minefield based on user input dimensions and allows the player to interact with the minefield through various commands.</p>

<h2>Features</h2>
<ul>
    <li>Customizable minefield dimensions and mine placements.</li>
    <li>Basic Minesweeper functionalities: flagging, question marking, and sweeping tiles.</li>
    <li>Automatic sweeping of adjacent empty tiles.</li>
    <li>Check win and loss conditions.</li>
    <li>Console-based user interface.</li>
</ul>

<h2>Getting Started</h2>
<h3>Prerequisites</h3>
<p>Ensure you have a C++ compiler installed on your system, such as <code>g++</code>.</p>

<h3>Compiling the Program</h3>
<p>To compile the program, navigate to the directory containing the source code and run:</p>
<pre><code>g++ -o minesweeper minesweeper.cpp</code></pre>

<h3>Running the Program</h3>
<p>After compiling, run the executable:</p>
<pre><code>./minesweeper</code></pre>

<h2>How to Play</h2>
<ol>
    <li>
        <p><strong>Input the dimensions of the minefield:</strong></p>
        <ul>
            <li>Enter the number of rows.</li>
            <li>Enter the number of columns.</li>
        </ul>
    </li>
    <li>
        <p><strong>Input the initial coordinates:</strong></p>
        <ul>
            <li>Enter the row and column of the initial tile to be swept.</li>
        </ul>
    </li>
    <li>
        <p><strong>Interacting with the Minefield:</strong></p>
        <ul>
            <li>The game will display the minefield with the initial tile swept.</li>
            <li>The player can perform the following actions by entering the corresponding commands:</li>
            <ul>
                <li><code>f</code> followed by row and column: Flag a tile.</li>
                <li><code>q</code> followed by row and column: Mark a tile with a question mark.</li>
                <li><code>s</code> followed by row and column: Sweep a tile.</li>
                <li><code>c</code> followed by row and column: Clear flags or question marks from a tile.</li>
            </ul>
        </ul>
    </li>
    <li>
        <p><strong>Game Status:</strong></p>
        <ul>
            <li>The number of swept tiles and flags used are displayed.</li>
            <li>The game ends if a mine is swept (loss) or if all non-mine tiles are swept (win).</li>
        </ul>
    </li>
</ol>

<h3>Example Commands</h3>
<p><code># Flag the tile at row 2, column 3</code><br>
<code>f 2 3</code></p>

<p><code># Mark the tile at row 4, column 1 with a question mark</code><br>
<code>q 4 1</code></p>

<p><code># Sweep the tile at row 0, column 0</code><br>
<code>s 0 0</code></p>

<p><code># Clear the flag or question mark from the tile at row 3, column 3</code><br>
<code>c 3 3</code></p>

<h2>Code Structure</h2>
<ul>
    <li><strong>Minefield Class:</strong> Handles the minefield's state, including mines, flags, and swept tiles. Contains methods for interacting with the minefield.</li>
    <li><strong>Main Function:</strong> Handles user input and output, manages the game loop.</li>
</ul>

<h2>Legend</h2>
<ul>
    <li><strong>F:</strong> Flagged tile</li>
    <li><strong>?</strong> Question marked tile</li>
    <li><strong> </strong> Unswept tile</li>
    <li><strong>o:</strong> Swept tile</li>
    <li><strong>*:</strong> Mine (displayed upon loss)</li>
</ul>

<h2>Notes</h2>
<ul>
    <li>The number of mines is set to the sum of the number of rows and columns.</li>
    <li>Ensure that initial coordinates do not contain a mine.</li>
</ul>

<h2>Contributing</h2>
<p>Feel free to fork this repository, create feature branches, and submit pull requests.</p>

<h2>License</h2>
<p>This project is licensed under the MIT License. See the <a href="LICENSE">LICENSE</a> file for details.</p>
