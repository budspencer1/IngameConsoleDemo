/*
* File Name: Console.cpp
* Author: Sebastian <3
* Date: 2016
* Purpose: Simple Console Source Code for Ingame Console
*/


#pragma once

#if ( !defined CONSOLE_SFML_INGAME )
	#define CONSOLE_SFML_INGAME 
#endif

#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

string res;

int main()
{
	RenderWindow rw( VideoMode( 1400 , 900 , 32 ) , ( "Ingame Console Demo - Press <T> to start console. /help and /version are commands. || Build: " __DATE__ " " __TIME__ "" ) , Style::Titlebar | Style::Close );
	rw.setVerticalSyncEnabled( true );
	rw.setMouseCursorVisible( false );

	bool isOpen = false;
	bool isVisible = false;

	static const unsigned int size = 20;
	static const unsigned int time = 5;

	Event mainevent;
	Font font;
	Text input;
	Text ident;
	Text output;
	string identS = ">>> ";
	string inputS = "";
	string outputS = "";
	string restore = "";
	std::string cmdchar = "";
	Clock clock; clock.restart();

	font.loadFromFile( string( "Cocogoose.otf" ) );

	input.setFont( font );
	input.setCharacterSize( size );
	input.setColor( sf::Color::White );
	input.setPosition( 90 , 800 );
	input.setString( string( inputS ) );

	ident.setFont( font );
	ident.setCharacterSize( size );
	ident.setColor( sf::Color::Cyan );
	ident.setPosition( 50 , 800 );
	ident.setString( string( identS ) );

	output.setFont( font );
	output.setCharacterSize( size );
	output.setColor( sf::Color::White );
	output.setPosition( 90 , 800 );
	output.setString( string( inputS ) );


	while( rw.isOpen() )
	{
		while( rw.pollEvent( mainevent ) )
		{
			if( isVisible )
			{
				if( clock.getElapsedTime().asSeconds() > time )
				{
					isVisible = false;
				}
			}

			if( mainevent.type == Event::Closed )
			{
				rw.close();
			}

			if( mainevent.type == Event::TextEntered )
			{
				if( isOpen )
				{
					if( mainevent.text.unicode == '\b' )
					{
						if( inputS != "" )
						{
							inputS.erase( inputS.size() - 1 , 1 );
						}
					}

					else

					{
						inputS += static_cast<char>( mainevent.text.unicode );
					}
				}
			}

			input.setString( string( inputS ) );
			

		if( Keyboard::isKeyPressed( Keyboard::Key::Return ) )
		{
			if( static_cast<string>( string( input.getString() ) ) != "" )
			{
				if( string( inputS ) == "/help" )
				{
					output.setColor( Color::White );
					output.setString( string( "List of Commands: /help , /version , /screenshot , /pause , /resume , /quit , /info" ) );
					clock.restart();
					isVisible = true;
				}

				else if( string( inputS ) == "/version" )
				{
					output.setColor( Color::White );
					output.setString( string( "Meteor Terminator - Version: Gamma 2.1.5_09 Rev: 1.8" ) );
					clock.restart();
					isVisible = true;
				}

				else
				{
					output.setColor( Color::Red );
					output.setString( string( "This command has not been found. Type /help for a commands list." ) );
					clock.restart();
					isVisible = true;
				}
			}

			inputS.erase();
			isOpen = false;
		}
	}

		if( Keyboard::isKeyPressed( Keyboard::Key::T ) )
		{
			if( !isOpen && !isVisible )
			{
				output.setColor( Color::White );
				output.setString( string( "" ) );

				isOpen = true;
				inputS.erase();
			}
		}

		if( Keyboard::isKeyPressed( Keyboard::Key::Escape ) )
		{
			if( isOpen )
			{
				inputS.erase();
				isOpen = false;
				inputS.erase();
			}
		}

		rw.clear( Color::Black );

		if( isOpen )
		{
			rw.draw( ident );
			rw.draw( input );
		}

		if( !isOpen && isVisible )
		{
			rw.draw( output );
		}

		rw.display();
	}
}