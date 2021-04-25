      Program Example
C Example of using of UpperLim.f on R58 data
C Example of the compilation instruction with GNU Fortran f77=g77:
C  f77 -g -o ExampleNew ExampleNew.f UpperLimNew.f y_vs_CLf.f CMaxinfNew.f ConfLevNew.f ConfLev.f Cinf.f CERN_Stuff.f
C Or, for gfortran,
C gfortran -frecord-marker=4 -o  ExampleNew ExampleNew.f UpperLimNew.f y_vs_CLf.f CMaxinfNew.f ConfLevNew.f ConfLev.f Cinf.f CERN_Stuff.f
C
C Read data from example.txt.  For each mass (GeV/c^2) show a range, if there
C is one, and an upper limit.  Within the range, and above the upper limit, the
C expected number of events and corresponding cross section are excluded.
      Implicit None
      Integer I,J,If,N,Iflag,EndPoints
      Character*6 dummy
      Real sigma,mu0,sigma0,muB,CL,sigcand(2)
      Real Mass(8),amu0(8),fc0,FC1(8),FC2(8),fc3,sigOptInt(8),
     1 Exclude_low
      Real UpperLim,FC(0:10) ! FC holds the data.  It can store up to 9 events.
      Common/UpperLimcom/EndPoints(2),Exclude_low(2)
C FC(0) is reserved for UpperLim use, as is FC(10) with 9 events.
C
      N=2 ! Two events
      If=1 ! fmin = 0.
      muB=0. ! Don't subtract background
C Assume cross section sigma0=1.E-42 cm^2 would produce expected number of
C events mu0.  Then the factor converting the upper limit expected number
C of events into the upper limit cross section is sigma0/mu0.
C      sigma0=1.e-6 ! In units of pb
      sigma0=10. ! In units of 10^{-7} pb
      open(20,file='example.txt',status='OLD',form='FORMATTED')
      read(20,2) dummy,(Mass(I),amu0(I),fc0,FC1(I),FC2(I),fc3,
     1 sigOptInt(I),I=1,8)
 2    Format(A6,/,(F6.1,F9.4,F3.0,2F13.9,F4.0,F11.5))
 10   Write(6,15)
 15   Format(/,'Give confidence level (like .89, 895, .9, .925, .93)',
     1  '; .le. 0 means stop')
      Read(5,*) CL
      If(CL.le.0.) Stop
      Write(6,16)
 16   Format('Which tables? Old (0), new (1), or the same (2)')
      Read(5,*) Iflag
      If(Iflag.eq.0) Then
         Call UseNewConfL(.false.)
         Call UseNewCMax(.false.)
      ElseIf(Iflag.eq.1) Then
         Call UseNewConfL(.true.)
         Call UseNewCMax(.true.)
      EndIf
      Write(6,20)
 20   Format(/,'Mass       Expected # of Events',6x,
     1 'Cross sections (10^{-7} pb)',/,13x,'Range',7x,'UpperLim',
     2     10x,'Range',7x,'UpperLim' )
      Do I=1,8
       FC(1)= FC1(I)
       FC(2)= FC2(I)
C Here we could put FC(0)=0.0 and FC(3)=1.0, but UpperLim will do it for us.
C 
       mu0=amu0(I)
       fc0=UpperLim(CL,If,N,FC,muB,FC,Iflag)
       sigma=(sigma0/mu0)*fc0
       If(Iflag.ge.256) Then
          Do J=1,2
             sigcand(J)=(sigma0/mu0)*Exclude_low(J)
          EndDo
          Write(6,25) Mass(I),Exclude_low,fc0,sigcand,sigma
 25       Format(F4.1,2x,2F8.4,2x,F8.4,4x,2F8.4,2x,F8.4)
       Else
          Write(6,30) Mass(I),fc0,sigma
 30       Format(F4.1,20x,F8.4,22x,F8.4)
       EndIf
      EndDo
      Goto 10
      End
