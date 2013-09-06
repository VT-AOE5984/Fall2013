
PROGRAM GaussFilter
    ! Variable declarations
    implicit None
    integer :: i,j,Nx,Ny,count
    integer :: start,stop,clock_rate,clock_max
    real*8 :: w0,w1,w2
    REAL*8,DIMENSION(:,:),ALLOCATABLE :: A,B

    ! Specify the input parameters
    Nx = 2848 
    Ny = 4288

    write(*,*)'Recursive Gaussian Filter'
    write(*,*)'Nx = ', Nx
    write(*,*)'Ny = ', Ny

    ! Allocate memory for the Input and output A	
    ALLOCATE(A(Nx,Ny))
    ALLOCATE(B(Nx,Ny))

    ! Read the image into the array A	
    OPEN(unit=1,file='Tetons.dat',access='STREAM',form='UNFORMATTED')
    READ(1) A

    ! Set the filter weights
    w0 = 1.0/3.0
    w1 = 1.0/9.0
    w2 = 1.0/18.0

    CALL SYSTEM_CLOCK(start,clock_rate,clock_max)   ! put a timer around the main work
    
    ! Recursively execute the Gaussian Filter 10 X
    DO count=1,10

        ! Execute the Gaussian Filter on the input A	
        DO i=2,Nx-1
            DO j=2,Ny-1
                B(i,j) = w0*A(i,j) + &
                    w1*(A(i+1,j)+A(i-1,j)+ &
                    A(i,j+1)+A(i,j-1)) + &
                    w2*(A(i+1,j+1)+A(i-1,j-1)+&
                    A(i+1,j-1)+A(i-1,j+1))
            END DO
        END DO
	
        ! B the filtered A
        DO i=2,Nx-1
            DO j=2,Ny-1
                A(i,j) = B(i,j)
            END DO
        END DO
    END DO
	    
    CALL SYSTEM_CLOCK(stop,clock_rate,clock_max)	! stop the timer
	
    WRITE(*,*) 'CPU Time = ', 1000*(stop-start)/real(clock_rate), 'milliseconds'

    ! Write the smoothed image to a binary file
    OPEN(unit=10,file='Smooth-Tetons.dat',status='UNKNOWN',access='STREAM',form='UNFORMATTED')
    WRITE(10)	B
	
END PROGRAM GaussFilter