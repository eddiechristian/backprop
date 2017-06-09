#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INP_NEURONS    4
#define HID_NEURONS   25
#define OUT_NEURONS    3

#define RHO 0.05

// Neuron cell values
double inputs[ INP_NEURONS+1 ];
double hidden[ HID_NEURONS+1 ];
double outputs[ OUT_NEURONS ];

// Weight values
double weights_hidden_input[ HID_NEURONS ][ INP_NEURONS+1 ];
double weights_output_hidden[ OUT_NEURONS ][ HID_NEURONS+1 ];

#define getSRand()      ( ( double ) rand( ) / ( double ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )
#define GetRandWeight( ) ( getSRand( ) - 0.5 )

// Test dataset with desired outputs (in a winner-takes-all fashion).
typedef struct dataset_s
{
   double inputs[ INP_NEURONS  ];
   double output[ OUT_NEURONS ];
} dataset_t;

dataset_t dataset[ ] = {
// Sepal Length, Sepal Width, Petal Length, Petal Width
                          // Iris-setosa
{ { 5.1, 3.5, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.9, 3.0, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.7, 3.2, 1.3, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.6, 3.1, 1.5, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.6, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.4, 3.9, 1.7, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 4.6, 3.4, 1.4, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.4, 1.5, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.4, 2.9, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.9, 3.1, 1.5, 0.1 }, { 1.0, 0.0, 0.0 } },
{ { 5.4, 3.7, 1.5, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.8, 3.4, 1.6, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.8, 3.0, 1.4, 0.1 }, { 1.0, 0.0, 0.0 } },
{ { 4.3, 3.0, 1.1, 0.1 }, { 1.0, 0.0, 0.0 } },
{ { 5.8, 4.0, 1.2, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.7, 4.4, 1.5, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 5.4, 3.9, 1.3, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.5, 1.4, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 5.7, 3.8, 1.7, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.8, 1.5, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 5.4, 3.4, 1.7, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.7, 1.5, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 4.6, 3.6, 1.0, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.3, 1.7, 0.5 }, { 1.0, 0.0, 0.0 } },
{ { 4.8, 3.4, 1.9, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.0, 1.6, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.4, 1.6, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 5.2, 3.5, 1.5, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.2, 3.4, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.7, 3.2, 1.6, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.8, 3.1, 1.6, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.4, 3.4, 1.5, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 5.2, 4.1, 1.5, 0.1 }, { 1.0, 0.0, 0.0 } },
{ { 5.5, 4.2, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.9, 3.1, 1.5, 0.1 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.2, 1.2, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.5, 3.5, 1.3, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.9, 3.1, 1.5, 0.1 }, { 1.0, 0.0, 0.0 } },
{ { 4.4, 3.0, 1.3, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.4, 1.5, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.5, 1.3, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 4.5, 2.3, 1.3, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 4.4, 3.2, 1.3, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.5, 1.6, 0.6 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.8, 1.9, 0.4 }, { 1.0, 0.0, 0.0 } },
{ { 4.8, 3.0, 1.4, 0.3 }, { 1.0, 0.0, 0.0 } },
{ { 5.1, 3.8, 1.6, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 4.6, 3.2, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.3, 3.7, 1.5, 0.2 }, { 1.0, 0.0, 0.0 } },
{ { 5.0, 3.3, 1.4, 0.2 }, { 1.0, 0.0, 0.0 } },
                          // Iris-versicolor
{ { 7.0, 3.2, 4.7, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 6.4, 3.2, 4.5, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 6.9, 3.1, 4.9, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 5.5, 2.3, 4.0, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 6.5, 2.8, 4.6, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 5.7, 2.8, 4.5, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 6.3, 3.3, 4.7, 1.6 }, { 0.0, 1.0, 0.0 } },
{ { 4.9, 2.4, 3.3, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 6.6, 2.9, 4.6, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 5.2, 2.7, 3.9, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 5.0, 2.0, 3.5, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 5.9, 3.0, 4.2, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 6.0, 2.2, 4.0, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 6.1, 2.9, 4.7, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 5.6, 2.9, 3.6, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 6.7, 3.1, 4.4, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 5.6, 3.0, 4.5, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 5.8, 2.7, 4.1, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 6.2, 2.2, 4.5, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 5.6, 2.5, 3.9, 1.1 }, { 0.0, 1.0, 0.0 } },
{ { 5.9, 3.2, 4.8, 1.8 }, { 0.0, 1.0, 0.0 } },
{ { 6.1, 2.8, 4.0, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 6.3, 2.5, 4.9, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 6.1, 2.8, 4.7, 1.2 }, { 0.0, 1.0, 0.0 } },
{ { 6.4, 2.9, 4.3, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 6.6, 3.0, 4.4, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 6.8, 2.8, 4.8, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 6.7, 3.0, 5.0, 1.7 }, { 0.0, 1.0, 0.0 } },
{ { 6.0, 2.9, 4.5, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 5.7, 2.6, 3.5, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 5.5, 2.4, 3.8, 1.1 }, { 0.0, 1.0, 0.0 } },
{ { 5.5, 2.4, 3.7, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 5.8, 2.7, 3.9, 1.2 }, { 0.0, 1.0, 0.0 } },
{ { 6.0, 2.7, 5.1, 1.6 }, { 0.0, 1.0, 0.0 } },
{ { 5.4, 3.0, 4.5, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 6.0, 3.4, 4.5, 1.6 }, { 0.0, 1.0, 0.0 } },
{ { 6.7, 3.1, 4.7, 1.5 }, { 0.0, 1.0, 0.0 } },
{ { 6.3, 2.3, 4.4, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 5.6, 3.0, 4.1, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 5.5, 2.5, 4.0, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 5.5, 2.6, 4.4, 1.2 }, { 0.0, 1.0, 0.0 } },
{ { 6.1, 3.0, 4.6, 1.4 }, { 0.0, 1.0, 0.0 } },
{ { 5.8, 2.6, 4.0, 1.2 }, { 0.0, 1.0, 0.0 } },
{ { 5.0, 2.3, 3.3, 1.0 }, { 0.0, 1.0, 0.0 } },
{ { 5.6, 2.7, 4.2, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 5.7, 3.0, 4.2, 1.2 }, { 0.0, 1.0, 0.0 } },
{ { 5.7, 2.9, 4.2, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 6.2, 2.9, 4.3, 1.3 }, { 0.0, 1.0, 0.0 } },
{ { 5.1, 2.5, 3.0, 1.1 }, { 0.0, 1.0, 0.0 } },
{ { 5.7, 2.8, 4.1, 1.3 }, { 0.0, 1.0, 0.0 } },
                          // Iris-virginica
{ { 6.3, 3.3, 6.0, 2.5 }, { 0.0, 0.0, 1.0 } },
{ { 5.8, 2.7, 5.1, 1.9 }, { 0.0, 0.0, 1.0 } },
{ { 7.1, 3.0, 5.9, 2.1 }, { 0.0, 0.0, 1.0 } },
{ { 6.3, 2.9, 5.6, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.5, 3.0, 5.8, 2.2 }, { 0.0, 0.0, 1.0 } },
{ { 7.6, 3.0, 6.6, 2.1 }, { 0.0, 0.0, 1.0 } },
{ { 4.9, 2.5, 4.5, 1.7 }, { 0.0, 0.0, 1.0 } },
{ { 7.3, 2.9, 6.3, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.7, 2.5, 5.8, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 7.2, 3.6, 6.1, 2.5 }, { 0.0, 0.0, 1.0 } },
{ { 6.5, 3.2, 5.1, 2.0 }, { 0.0, 0.0, 1.0 } },
{ { 6.4, 2.7, 5.3, 1.9 }, { 0.0, 0.0, 1.0 } },
{ { 6.8, 3.0, 5.5, 2.1 }, { 0.0, 0.0, 1.0 } },
{ { 5.7, 2.5, 5.0, 2.0 }, { 0.0, 0.0, 1.0 } },
{ { 5.8, 2.8, 5.1, 2.4 }, { 0.0, 0.0, 1.0 } },
{ { 6.4, 3.2, 5.3, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 6.5, 3.0, 5.5, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 7.7, 3.8, 6.7, 2.2 }, { 0.0, 0.0, 1.0 } },
{ { 7.7, 2.6, 6.9, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 6.0, 2.2, 5.0, 1.5 }, { 0.0, 0.0, 1.0 } },
{ { 6.9, 3.2, 5.7, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 5.6, 2.8, 4.9, 2.0 }, { 0.0, 0.0, 1.0 } },
{ { 7.7, 2.8, 6.7, 2.0 }, { 0.0, 0.0, 1.0 } },
{ { 6.3, 2.7, 4.9, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.7, 3.3, 5.7, 2.1 }, { 0.0, 0.0, 1.0 } },
{ { 7.2, 3.2, 6.0, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.2, 2.8, 4.8, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.1, 3.0, 4.9, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.4, 2.8, 5.6, 2.1 }, { 0.0, 0.0, 1.0 } },
{ { 7.2, 3.0, 5.8, 1.6 }, { 0.0, 0.0, 1.0 } },
{ { 7.4, 2.8, 6.1, 1.9 }, { 0.0, 0.0, 1.0 } },
{ { 7.9, 3.8, 6.4, 2.0 }, { 0.0, 0.0, 1.0 } },
{ { 6.4, 2.8, 5.6, 2.2 }, { 0.0, 0.0, 1.0 } },
{ { 6.3, 2.8, 5.1, 1.5 }, { 0.0, 0.0, 1.0 } },
{ { 6.1, 2.6, 5.6, 1.4 }, { 0.0, 0.0, 1.0 } },
{ { 7.7, 3.0, 6.1, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 6.3, 3.4, 5.6, 2.4 }, { 0.0, 0.0, 1.0 } },
{ { 6.4, 3.1, 5.5, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.0, 3.0, 4.8, 1.8 }, { 0.0, 0.0, 1.0 } },
{ { 6.9, 3.1, 5.4, 2.1 }, { 0.0, 0.0, 1.0 } },
{ { 6.7, 3.1, 5.6, 2.4 }, { 0.0, 0.0, 1.0 } },
{ { 6.9, 3.1, 5.1, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 5.8, 2.7, 5.1, 1.9 }, { 0.0, 0.0, 1.0 } },
{ { 6.8, 3.2, 5.9, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 6.7, 3.3, 5.7, 2.5 }, { 0.0, 0.0, 1.0 } },
{ { 6.7, 3.0, 5.2, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 6.3, 2.5, 5.0, 1.9 }, { 0.0, 0.0, 1.0 } },
{ { 6.5, 3.0, 5.2, 2.0 }, { 0.0, 0.0, 1.0 } },
{ { 6.2, 3.4, 5.4, 2.3 }, { 0.0, 0.0, 1.0 } },
{ { 5.9, 3.0, 5.1, 1.8 }, { 0.0, 0.0, 1.0 } }
};

#define MAX_TESTS ( sizeof( dataset ) / sizeof( dataset_t ) )

#define sigmoid( x )    ( 1.0 / ( 1.0 + exp( -x ) ) )
#define sigmoid_d( x )  ( x * ( 1.0 - x ) )
#define sqr( x )        ( x * x )

// Initialize the network with random weights.
void NN_Initialize( void )
{
   int i, j;

   inputs[ INP_NEURONS ] = 1.0;

   hidden[ HID_NEURONS ] = 1.0;

   for ( j = 0 ; j < HID_NEURONS ; j++ )
   {
      for ( i = 0 ; i < INP_NEURONS ; i++ )
      {
         weights_hidden_input[ j ][ i ] = GetRandWeight( );
      }
   }

   for ( j = 0 ; j < OUT_NEURONS ; j++ )
   {
      for ( i = 0 ; i < HID_NEURONS ; i++ )
      {
         weights_output_hidden[ j ][ i ] = GetRandWeight( );
      }
   }

}

// Given the test input, feed forward to the output.
int NN_Feed_Forward( void )
{
   int i, j, best;
   double max;

   // Calculate hidden layer outputs
   for ( i = 0 ; i < HID_NEURONS ; i++ )
   {
      hidden[ i ] = 0.0;

      for ( j = 0 ; j < INP_NEURONS+1; j++ )
      {
         hidden[ i ] += ( weights_hidden_input[ i ][ j ] * inputs[ j ] );
      }
      hidden[ i ] = sigmoid( hidden[ i ] );
   }

   // Calculate output layer outputs
   for ( i = 0 ; i < OUT_NEURONS ; i++ )
   {
      outputs[ i ] = 0.0;
      for ( j = 0 ; j < HID_NEURONS+1 ; j++ )
      {
         outputs[ i ] += ( weights_output_hidden[ i ][ j ] * hidden[ j ] );
      }
      outputs[ i ] = sigmoid( outputs[ i ] );
   }

   // Perform winner-takes-all for the network.
   best = 0;
   max = outputs[ 0 ];

   for ( i = 1 ; i < OUT_NEURONS ; i++ )
   {
      if ( outputs[ i ] > max )
      {
         best = i;
         max = outputs[ i ];
      }
   }

   return best;
}

// Given a classification, backpropagate the error through the weights.
void NN_Backpropagate( int test )
{
   int out, hid, inp;

   double err_out[ OUT_NEURONS ];
   double err_hid[ HID_NEURONS ];

   // Calculate output node error
   for ( out = 0 ; out < OUT_NEURONS ; out++ )
   {
      err_out[ out ] = ( ( double ) dataset[ test ].output[ out ] - outputs[ out ] ) * 
                          sigmoid_d( outputs[ out ] );
   }

   // Calculate the hidden node error
   for ( hid = 0 ; hid < HID_NEURONS ; hid++ )
   {
      err_hid[ hid ] = 0.0;
      for ( out = 0 ; out < OUT_NEURONS ; out++ )
      {
         err_hid[ hid ] += err_out[ out ] * weights_output_hidden[ out ][ hid ];
      }
      err_hid[ hid ] *= sigmoid_d( hidden[ hid ] );
   }

   // Adjust the hidden to output layer weights
   for ( out = 0 ; out < OUT_NEURONS ; out++ )
   {
      for ( hid = 0 ; hid < HID_NEURONS ; hid++ )
      {
         weights_output_hidden[ out ][ hid ] += RHO * err_out[ out ] * hidden[ hid ];
      }
   }

   // Adjust the input to hidden layer weights
   for ( hid = 0 ; hid < HID_NEURONS ; hid++ )
   {
      for ( inp = 0 ; inp < INP_NEURONS+1 ; inp++ )
      {
         weights_hidden_input[ hid ][ inp ] += RHO * err_hid[ hid ] * inputs[ inp ];
      }
   }

}

// Calculate the MSE for the desired output.
double MSE_Calculate( int test )
{
   double mse = 0.0;
   int i;

   for ( i = 0 ; i < OUT_NEURONS ; i++ )
   {
      mse += sqr( ( dataset[ test ].output[ i ] - outputs[ i ] ) );
   }

   return mse;
}

// Set the test input vector.
void NN_Set_Inputs( int test )
{
   int i;

   for ( i = 0 ; i < INP_NEURONS ; i++ )
   {
      inputs[ i ] = dataset[ test ].inputs[ i ];
   }

   return;
}

// Train the network from the test vectors.
void NN_Train( double min_mse )
{
   double mse;
   int test;

   do
   {
      test = getRand( MAX_TESTS );

      NN_Set_Inputs( test );

      (void)NN_Feed_Forward( );

      NN_Backpropagate( test );

      mse = MSE_Calculate( test );

      printf( "mse = %g\n", mse );

   } while ( mse > min_mse );

   return;
}

// Test the network given random vectors.
void NN_Test( int tests )
{
   int i, test, result;

   for ( i = 0 ; i < tests ; i++ )
   {
      test = getRand( MAX_TESTS );

      NN_Set_Inputs( test );

      result = NN_Feed_Forward( );

      printf( "Test %d classifed as %d\n", test, result );
      printf( "Test %d outputs %g %g %g\n", test, 
               dataset[test].output[0],
               dataset[test].output[1],
               dataset[test].output[2] );
   } 

   return;
}


int main( void )
{
   srand( time( NULL ) );

   NN_Initialize( );

   NN_Train( 0.0001 );

   NN_Test( 10 );

   return 0;
}

