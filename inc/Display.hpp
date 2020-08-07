#pragma once

#include "SFML/Graphics.hpp"
#include "Board.hpp"
#include "TField.hpp"

/**
 * \brief Care about display on the interface.
 *
 */
class Display {
private:
    /**
     * \brief Templates of Field view. Default: array of NULL.
     *
     * id   | name
     * :----|:--------
     * 0    | empty
     * 1-8  | values
     * 9    | mine
     * 10   | flag
     * 11   | covered
     *
     * \see NUM_FIELD_VIEW, TField
     */
    static TField* Template[NUM_FIELD_VIEW ];

    sf::Texture flag_texture;       ///< Click mode flag texture
    sf::Texture click_texture;      ///< Click mode "click" texture
    sf::Sprite  mode_butt;          ///< Mode button spirte

    sf::Texture score_texture;      ///< Score counter backgroun texture
    sf::Sprite  score_bg;           ///< Score counter background
    sf::Text    score_txt;          ///< Score counter text

    sf::Font    font;               ///< Font


private:
    /**
     * \brief Field code to element on Templete array.
     * \param field - value of field
     * \return short int - id in the Templete array.
     */
    static TField* const pointer( const Field& field );

public:
    /**
     * \brief Construct a new Display object
     */
    Display() = default;

    /**
     * \brief Config a Display class.
     * \post
     *  todo docs
     */
    void config( const Vector2D& size );

    /**
     * \brief Destroy the Display object
     */
    ~Display();

public:
    /**
     * \brief Change a view of mode button
     * \post Change texture in butt_mode
     */
    void changeButt( const bool mode );

public:
    /**
     * \brief Display board on the window
     * \param target - window target
     * \param board - game board
     */
    void board( sf::RenderTarget& target, const Board* const board ) const;

    /**
     * \brief Draw a interface of the game.
     * \param target - window target
     */
    void draw( sf::RenderTarget& target ) const;

    /**
     * \brief Update a value of stopwatch time.
     * \param seconds -
     */
    void stopwatch( unsigned int seconds );
    //idea make inline

    /**
     * \brief Update value of score on the display
     * \param score -
     */
    void score( unsigned int score );
    //idea make inline


};