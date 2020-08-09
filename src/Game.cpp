#include "Game.hpp"
#include <sstream>

using namespace std;
using namespace sf;

////----------------------------------------------------------------------
Game::Game( const int argc, const char* const argv[] ){
    int id = 1;
    unsigned int w = DEFAULT_X_SIZE,
                 h = DEFAULT_Y_SIZE,
                 m = DEFAULT_MINE;
    stringstream strm;

    while( id < argc ){

        if( argv[id][0] == '-' ){
            switch( argv[id][1] ){

            ///- `w` - width of the board
            case 'w':
                strm << argv[ ++id ] << ' ';
                strm >> w;
                break;

            ///- `h` - height of the board
            case 'h':
                strm << argv[ ++id ] << ' ';
                strm >> h;
                break;

            ///- `m` - number of mines
            case 'm':
                strm << argv[ ++id ] << ' ';
                strm >> m;
                break;

            ///- Unknow argument
            default:
                cerr << "!!! Warning: unknow input argument" << endl
                     << "! " << argv[id] << endl;
            }
        }
        else {
            cerr << "!!! Warning: unknow input argument" << endl
                 << "! " << argv[id] << endl;
        }

        ++id;
    }

    ///- Config Board
    this->board.set( w, h, m );

    ///- Config Display
    this->display.config( Vector2D(w,h) );

    ///- Init values
    this->buttRev = false;
}

////----------------------------------------------------------------------
void Game::finish(){
    running = false;                ///- Set running to false

    //todo end game message
}

////----------------------------------------------------------------------
void Game::start(){
    ///- Stopwatch clear
    clock.restart();
    stopwatch = 0;

    ///- Clear board
    this->board.restart();          ///- Restart the board

    ///- Start running mode
    running = true;
}

////----------------------------------------------------------------------
void Game::click( const sf::RenderWindow& window, const sf::Mouse::Button butt ){

    Vector2i mouse_pos = Mouse::getPosition(window);

    ///- Check the click is in the window
    if( mouse_pos.x < 0 || mouse_pos.x > width() ) return;
    if( mouse_pos.y < 0 || mouse_pos.y > height() ) return;

    if( this->isOn() ){

        if( mouse_pos.y > GUI_MARGIN_T ){       //inside board

            if( this->firstAction( butt ) ){
                ///- First action on the board: uncover the field.
                this->board.uncover( Game::position( mouse_pos ) );
            }
            else {
                if( this->board.created() )
                    ///- Second action on the covered field: flag the field.
                    /// If field is uncovered: if it's possible uncover fields around.
                    this->board.action( Game::position( mouse_pos ) );
                else
                    ///- If board isn't created, second move is create and uncover too.
                    this->board.uncover( Game::position( mouse_pos ) );
            }
        }
        else {                                  // outside board (top bar)
            buttRev = ! buttRev;
            this->display.changeButt( buttRev );
        }
    }
    else {
        ///- Start the game
        this->start();
    }
}

////----------------------------------------------------------------------
Vector2D Game::position( const sf::Vector2i& pos )
{ return Vector2D( pos.x/FIELD_SIZE, (pos.y-GUI_MARGIN_T)/FIELD_SIZE ); }

////----------------------------------------------------------------------
void Game::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    this->display.board( target, &this->board );
    this->display.draw( target );

    if( ! this->isOn() ) this->display.drawStart( target );
}

////----------------------------------------------------------------------
void Game::update(){
    this->display.score( this->board.noFlaggedMines() );
    this->display.stopwatch( this->time() );
}