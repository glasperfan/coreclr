// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

/*=====================================================================
**
** Source:  test1.c (exception_handling\pal_except\test1)
**
** Purpose: Test to make sure the PAL_EXCEPT block is executed
**          after an exception occurs in the PAL_TRY block
**
**
**===================================================================*/
#include <palsuite.h>

/* Execution flags */
BOOL bTry    = FALSE;
BOOL bExcept = FALSE;

int __cdecl main(int argc, char *argv[])
{
    if (0 != PAL_Initialize(argc, argv))
    {
        return FAIL;
    }

    PAL_TRY 
    {
        int* p = 0x00000000;   /* NULL pointer */

        bTry = TRUE;    /* indicate we hit the PAL_TRY block */
        *p = 13;        /* causes an access violation exception */

        Fail("ERROR: code was executed after the access violation.\n");
    }
    PAL_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        if (!bTry)
        {
            Fail("ERROR: PAL_EXCEPT was hit without PAL_TRY being hit.\n");
        }

        bExcept = TRUE; /* indicate we hit the PAL_EXCEPT block */
    }
    PAL_ENDTRY;

    if (!bTry)
    {
        Trace("ERROR: the code in the PAL_TRY block was not executed.\n");
    }

    if (!bExcept)
    {
        Trace("ERROR: the code in the PAL_EXCEPT block was not executed.\n");
    }

    /* did we hit all the code blocks? */
    if(!bTry || !bExcept)
    {
        Fail("");
    }


    PAL_Terminate();  
    return PASS;

}
