//
//  main.cpp
//  LCS
//
//  Created by 林仁鴻 on 2018/8/20.
//  Copyright © 2018年 林仁鴻. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void inputString( string & );
void lcsTraversal( string, int **, int, int );
void lcsTraversalHelper( string, int **, int, int );
template< typename T > void removeTheSame( vector< T > &vecRef );

vector< string > possility;
string sequence = "";

int main()
{
    string firstGene, secondGene;
    int **compareArray;
    
    
    inputString( firstGene );
    inputString( secondGene );
    cout << endl;
    
    const int rows = secondGene.size(), columns = firstGene.size();
    
    
    compareArray = new int*[ rows ];
    
    for( int i = 0; i < rows; i++ )
        *( compareArray + i ) = new int[ columns ];
    
    
    
    
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
            if( i == 0 || j == 0 )
                compareArray[ i ][ j ] = 0;
            
            else if( ( firstGene[ j ] == secondGene[ i ] ) &&
                    ( ( i > 0 ) && ( j > 0 ) ) )
                compareArray[ i ][ j ] = compareArray[ i - 1 ][ j - 1 ] + 1;
            
            else if( ( firstGene[ j ] != secondGene[ i ] ) &&
                    ( ( i > 0 ) && ( j > 0 ) ) )
                compareArray[ i ][ j ] = max( compareArray[ i ][ j - 1 ], compareArray[ i - 1 ][ j ] );
        }
    }
    
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
            cout << setw( 3 ) << compareArray[ i ][ j ];
        }
        cout << endl;
    }
    
    cout << endl;
    
    lcsTraversal( firstGene, compareArray, rows - 1, columns - 1 );
    for( int i = 0; i < possility.size(); i++ )
        cout << "LCS = " << possility[ i ] << endl;
    
    for( int i = 0; i < rows; i++ )
        delete [] ( *( compareArray + i ) );
    delete [] compareArray;
}



void inputString( string &s )
{
    getline( cin, s );
    s.insert( 0, "0" );
}



void lcsTraversal( string gene, int ** order, int i, int j )
{
    if( order[ i ][ j ] == order[ i - 1 ][ j ] && order[ i ][ j ] == order[ i ][ j - 1 ] )
    {
        lcsTraversalHelper( gene, order, i - 1, j );
        sequence = "";
        lcsTraversalHelper( gene, order, i, j - 1 );
        sequence = "";
    }
    else
    {
        if( order[ i ][ j ] == order[ i - 1 ][ j ] )
        {
            lcsTraversalHelper( gene, order, i, j );
            sequence = "";
        }
        else
        {
            lcsTraversalHelper( gene, order, i, j );
            sequence = "";
        }
    }
    removeTheSame( possility );
    sort( possility.begin(), possility.end() );
}


void lcsTraversalHelper( string gene, int ** order, int i, int j )
{
    if( i == 0 || j == 0 )
    {
        reverse( sequence.begin(), sequence.end() );
        possility.push_back( sequence );
        reverse( sequence.begin(), sequence.end() );
        return;
    }
    
    else if( order[ i ][ j ] == order[ i - 1 ][ j ] && order[ i ][ j ] == order[ i ][ j - 1 ] )
    {
        string temp = sequence;
        lcsTraversalHelper( gene, order, i - 1, j );
        sequence = temp;
        string temp2 = sequence;
        lcsTraversalHelper( gene, order, i, j - 1 );
        sequence = temp2;
    }
    
    else if( order[ i ][ j ] == order[ i - 1 ][ j ] )
        lcsTraversalHelper( gene, order, i - 1, j );
    
    else if( order[ i ][ j ] == order[ i ] [ j - 1 ] )
        lcsTraversalHelper( gene, order, i, j - 1 );
    
    else if( order[ i ][ j ] > order[ i - 1 ][ j - 1 ] )
    {
        sequence += gene[ j ];
        lcsTraversalHelper( gene, order, i - 1, j - 1 );
    }
    
}




template< typename T >
void removeTheSame( vector< T > &vecRef )
{
    sort( vecRef.begin(), vecRef.end() );
    vecRef.erase( unique( vecRef.begin(), vecRef.end() ), vecRef.end() );
}
