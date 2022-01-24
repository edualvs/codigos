var board = null;
var game = new Chess();
var $status = $('#status');
var $pgn = $('#pgn');
var $tabuleiro = $('#meuTabuleiro');

function onDragStart (source, piece, position, orientation) {
  // não movimenta as peças se o jogo acabou
  if (game.game_over()) return false;

  // movimenta as peças somente do lado que possui a vez
  if ((game.turn() === 'w' && piece.search(/^b/) !== -1) ||
      (game.turn() === 'b' && piece.search(/^w/) !== -1)) {
    return false;
  }
}

function onDrop (source, target) {
  // Verifica se o movimento é válido
  var move = game.move({
    from: source,
    to: target,
    promotion: 'q' // OBS: A promoção é sempre para a DAMA
  })

  //Movimento inválido
  if (move === null) return 'snapback';

  updateStatus();
}

// Atualiza o tabuleiro depois de um lance
// importante para o roque, en passant, promoção
function onSnapEnd () {
  board.position(game.fen())
}

function updateStatus () {
  var status = '';

  var moveCor = 'White';
  if (game.turn() === 'b') {
    moveCor = 'Black';
  }

  // checkmate?
  if (game.in_checkmate()) {
    pauseW();
    pauseB();
    status = 'Game over, ' + moveCor + ' is in checkmate.';
    
  }

  // draw?
  else if (game.in_draw()) {
    pauseW();
    pauseB();
    status = 'Game over, drawn position';
  }

  // game still on
  else {
    status = moveCor + ' to move';

    // check?
    if (game.in_check()) {
      status += ', ' + moveCor + ' is in check';
    }
  }

  var turno = game.turn();
  if (turno === 'b'){
    startW();
    pauseB();
  }
  else{
    pauseW();
    startB();
  }

  if(document.getElementById('counterBlack').innerHTML === '00:00'){
    alert('O tempo das brancas se esgotou, vitória das pretas')
  }

  if(document.getElementById('counterWhite').innerHTML === '00:00'){
    alert('O tempo das pretas se esgotou, vitória das brancas')
  }

  $status.html(status)
  $pgn.html(game.pgn())
}

var config = {
  draggable: true,
  position: 'start',
  onDragStart: onDragStart,
  onDrop: onDrop,
  onSnapEnd: onSnapEnd
}

board = Chessboard('meuTabuleiro', config)

function reinicia(){
  board = Chessboard('meuTabuleiro', config)
  game.reset();
  pararW();
  pararB();
}

updateStatus()
