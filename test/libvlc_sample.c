#include <stdio.h>
#include <time.h>
#include <vlc/libvlc.h>

int main(int argc, char **argv)
{
    libvlc_instance_t *p_instance1;
    libvlc_exception_t exception;
    libvlc_input_t    *p_input;
    int b_started = 0;

    libvlc_exception_init( &exception );
    
    p_instance1 = libvlc_new( argc,argv, &exception );

    if( libvlc_exception_raised( &exception ) )
    {
        fprintf( stderr, "FATAL: %s\n",
                        libvlc_exception_get_message( &exception ) );
        return 0; 
    }

    fprintf (stderr, "Playing\n");
    libvlc_playlist_play( p_instance1, 0, 0,NULL, NULL );
    fprintf (stderr, "Playback started\n");

    while( 1 )
    {
        sleep( 1 );
        libvlc_exception_init( &exception );
        p_input = libvlc_playlist_get_input( p_instance1, &exception );

        if( libvlc_exception_raised( &exception ) )
        {
           if( b_started == 1 )
               break;
           else
               continue;
        }
        else
        {
            b_started = 1;
        }

        libvlc_toggle_fullscreen( p_input, &exception );
        if( libvlc_exception_raised( &exception ) )
        {
            fprintf( stderr, "EX : %s\n", libvlc_exception_get_message( &exception ) );
        }
        fprintf( stderr, "Length %lli - Time %lli - Full screen %i\n", 
                              libvlc_input_get_length( p_input, NULL ),
                              libvlc_input_get_time( p_input, NULL ), 
                              libvlc_get_fullscreen( p_input, NULL ) );
        libvlc_input_free( p_input );
    }

    libvlc_destroy( p_instance1 );
       
    return 0;
}
