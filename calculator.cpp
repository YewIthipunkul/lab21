#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND TextBox1,TextBox2;
HWND textfield,buttonplus,buttonminus,buttontime,buttondiv;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(255,255,0));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "My Calculator",     /* Title Text */
           WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key meSages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        textfield = CreateWindow("STATIC",
                                 "Please input two numbers",
                                 WS_VISIBLE | WS_CHILD ,
                                 20,20,200,25,hwnd,NULL,NULL,NULL);
        TextBox1 = CreateWindow("EDIT",
                               "",
                               WS_CHILD | WS_VISIBLE| WS_BORDER | ES_AUTOHSCROLL,
                               40,50,150,25,hwnd,(HMENU) 100,NULL,NULL);
        TextBox2 = CreateWindow("EDIT",
                                "",
                                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                40,80,150,25,hwnd,(HMENU) 101,NULL,NULL);

        buttonplus = CreateWindow("BUTTON",
                              "+",
                              WS_VISIBLE | WS_CHILD,
                              50,120,20,20,hwnd,(HMENU) 1,NULL,NULL);
        buttonminus = CreateWindow("BUTTON",
                                   "-",
                                   WS_CHILD| WS_VISIBLE,
                                   90,120,20,20,hwnd,(HMENU) 2,NULL,NULL);
        buttontime = CreateWindow("BUTTON",
                                   "*",
                                   WS_CHILD| WS_VISIBLE,
                                   130,120,20,20,hwnd,(HMENU) 3,NULL,NULL);
        buttondiv = CreateWindow("BUTTON",
                                   "/",
                                   WS_CHILD| WS_VISIBLE,
                                   170,120,20,20,hwnd,(HMENU) 4,NULL,NULL);

        break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 100 || LOWORD(wParam) == 101)
                break;

            char buffer1[256],buffer2[256];
            double num1,num2,result;
            GetWindowText(TextBox1,buffer1,256);
            GetWindowText(TextBox2,buffer2,256);

            num1 = atof(buffer1);
            num2 = atof(buffer2);
            switch(LOWORD(wParam))
            {
                case 1:
                    result = num1+num2;
                    break;
                case 2:
                    result = num1   um2;
                    break;
                case 3:
                    result = num1*num2;
                    break;
                case 4:
                    result = num1 / num2;
                    break;
            }
            char t[100];
            double x;
            sprintf(t,"%f",result);
            ::MessageBox(hwnd, t, "Result", x);
            break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
