n
n - diesen Patch-Block nicht aus Staging-Area entfernen
q - Beenden; diesen oder alle verbleibenden Patch-Blöcke nicht aus Staging-Area entfernen
a - diesen und alle weiteren Patch-Blöcke dieser Datei aus Staging-Area entfernen
d - diesen oder alle weiteren Patch-Blöcke dieser Datei nicht aus Staging-Area entfernen
 Sie wechseln den Branch während einer binären Suche Es befinden sich zum Commit vorgemerkte Änderungen in Ihrem Arbeitsverzeichnis.
Wenn diese Änderungen in den vorherigen Commit aufgenommen werden sollen,
führen Sie aus:

  git commit --amend %s

Wenn daraus ein neuer Commit erzeugt werden soll, führen Sie aus:

  git commit %s

Im Anschluss führen Sie zum Fortfahren aus:

  git rebase --continue
 Sie könnten diese aufräumen oder wiederherstellen. Sie könnten die Variable %s auf mindestens %d setzen und den Befehl
erneut versuchen. Sie müssen Pfad(e) zur Wiederherstellung angeben. Sie müssen zuerst die Konflikte in Ihrem aktuellen Index auflösen. Ihr aktueller Branch '%s' hat noch keine Commits. Ihr aktueller Branch scheint fehlerhaft zu sein. Ihre Index-Datei ist nicht zusammengeführt. Ihre lokalen Änderungen würden durch den %s überschrieben werden. Ihre Datei für den partiellen Checkout hat eventuell Probleme:
Muster '%s' wiederholt sich. PRIuMAX PRIx32 PRIx64 PRIu32 timestamp too large for this system: % commit date for commit %s in commit-graph is % != % % second ago %<PRIuMAX> seconds ago % minute ago %<PRIuMAX> minutes ago % hour ago %<PRIuMAX> hours ago % day ago %<PRIuMAX> days ago % week ago %<PRIuMAX> weeks ago % month ago %<PRIuMAX> months ago % year %<PRIuMAX> years %s, % month ago %s, %<PRIuMAX> months ago % year ago %<PRIuMAX> years ago oid fanout out of order: fanout[%d] = % > % = fanout[%d] incorrect object offset for oid[%d] = %s: % != % attempting to mmap % over limit % gc is already running on machine '%s' pid % (use --force if not) pack version % unsupported pack has bad object at offset %: %s premature end of pack file, % byte missing premature end of pack file, %<PRIuMAX> bytes missing bad pack.indexversion=% ordered %u objects, expected % wrote % objects while expecting % object %s inconsistent object length (% vs %) Total % (delta %), reused % (delta %), pack-reused % short read (expected % bytes, read %) Timestamp zu groß für dieses System: % Commit-Datum für Commit %s in Commit-Graph ist % != % vor % Sekunde vor % Sekunden vor % Minute vor % Minuten vor % Stunde vor % Stunden vor % Tag vor % Tagen vor % Woche vor % Wochen vor % Monat vor % Monaten vor % Jahr vor % Jahren %s, und % Monat %s, und % Monaten vor % Jahr vor % Jahren Ungültige oid fanout Reihenfolge: fanout[%d] = % > % = fanout[%d] Falscher Objekt-Offset für oid[%d] = %s: % != % Versuche mmap % über Limit %. "git gc" wird bereits auf Maschine '%s' pid % ausgeführt
(benutzen Sie --force falls nicht) Paketversion % nicht unterstützt Paket hat ein ungültiges Objekt bei Versatz %: %s frühzeitiges Ende der Paketdatei, vermisse % Byte frühzeitiges Ende der Paketdatei, vermisse % Bytes "pack.indexversion=%" ist ungültig %u Objekte geordnet, % erwartet. Schrieb % Objekte während % erwartet waren. Inkonsistente Objektlänge bei Objekt %s (% vs %) Gesamt % (Delta %), Wiederverwendet % (Delta %), Pack wiederverwendet % read() zu kurz (% Bytes erwartet, % gelesen)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ### Application-specific constants

APP_NAME := util_spi_stress

### Environment constants 

LGW_PATH ?= ../libloragw
ARCH ?=
CROSS_COMPILE ?=

### External constant definitions
# must get library build option to know if mpsse must be linked or not

include $(LGW_PATH)/library.cfg

### Constant symbols

CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar

CFLAGS=-O2 -Wall -Wextra -std=c99 -Iinc -I.

OBJDIR = obj

### Constants for LoRa concentrator HAL library
# List the library sub-modules that are used by the application

LGW_INC = $(LGW_PATH)/inc/config.h
LGW_INC += $(LGW_PATH)/inc/loragw_reg.h

### Linking options

LIBS := -lloragw -lrt -lm

### General build targets

all: $(APP_NAME)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(APP_NAME)

### HAL library (do no force multiple library rebuild even with 'make -B')

$(LGW_PATH)/inc/config.h:
	@if test ! -f $@; then \
	$(MAKE) all -C $(LGW_PATH); \
	fi

$(LGW_PATH)/libloragw.a: $(LGW_INC)
	@if test ! -f $@; then \
	$(MAKE) all -C $(LGW_PATH); \
	fi

### Main program compilation and assembly

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/$(APP_NAME).o: src/$(APP_NAME).c $(LGW_INC) | $(OBJDIR)
	$(CC) -c $(CFLAGS) -I$(LGW_PATH)/inc $< -o $@

$(APP_NAME): $(OBJDIR)/$(APP_NAME).o $(LGW_PATH)/libloragw.a
	$(CC) -L$(LGW_PATH) $< -o $@ $(LIBS)

### EOF
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       /*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
  (C)2013 Semtech-Cycleo

Description:
    SPI stress test

License: Revised BSD License, see LICENSE.TXT file include in the project
Maintainer: Sylvain Miermont
*/


/* -------------------------------------------------------------------------- */
/* --- DEPENDANCIES --------------------------------------------------------- */

/* fix an issue between POSIX and C99 */
#if __STDC_VERSION__ >= 199901L
    #define _XOPEN_SOURCE 600
#else
    #define _XOPEN_SOURCE 500
#endif

#include <stdint.h>     /* C99 types */
#include <stdbool.h>    /* bool type */
#include <stdio.h>      /* printf fprintf sprintf fopen fputs */

#include <signal.h>     /* sigaction */
#include <unistd.h>     /* getopt access */
#include <stdlib.h>     /* rand */

#include "loragw_reg.h"

/* -------------------------------------------------------------------------- */
/* --- PRIVATE MACROS ------------------------------------------------------- */

#define ARRAY_SIZE(a)    (sizeof(a) / sizeof((a)[0]))
#define MSG(args...)    fprintf(stderr, args) /* message that is destined to the user */

/* -------------------------------------------------------------------------- */
/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#define VERS                    103
#define READS_WHEN_ERROR        16 /* number of times a read is repeated if there is a read error */
#define BUFF_SIZE               1024 /* maximum number of bytes that we can write in sx1301 RX data buffer */
#define DEFAULT_TX_NOTCH_FREQ   129E3

/* -------------------------------------------------------------------------- */
/* --- PRIVATE VARIABLES (GLOBAL) ------------------------------------------- */

/* signal handling variables */
struct sigaction sigact; /* SIGQUIT&SIGINT&SIGTERM signal handling */
static int exit_sig = 0; /* 1 -> application terminates cleanly (shut down hardware, close open files, etc) */
static int quit_sig = 0; /* 1 -> application terminates without shutting down the hardware */

/* -------------------------------------------------------------------------- */
/* --- PRIVATE FUNCTIONS DECLARATION ---------------------------------------- */

static void sig_handler(int sigio);

void usage (void);

/* -------------------------------------------------------------------------- */
/* --- PRIVATE FUNCTIONS DEFINITION ----------------------------------------- */

static void sig_handler(int sigio) {
    if (sigio == SIGQUIT) {
        quit_sig = 1;;
    } else if ((sigio == SIGINT) || (sigio == SIGTERM)) {
        exit_sig = 1;
    }
}

/* describe command line options */
void usage(void) {
    MSG( "Available options:\n");
    MSG( " -h print this help\n");
    MSG( " -t <int> specify which test you want to run (1-4)\n");
}

/* -------------------------------------------------------------------------- */
/* --- MAIN FUNCTION -------------------------------------------------------- */

int main(int argc, char **argv)
{
    int i;
    int xi = 0;

    /* application option */
    int test_number = 1;
    int cycle_number = 0;
    int repeats_per_cycle = 1000;
    bool error = false;

    /* in/out variables */
    int32_t test_value;
    int32_t read_value;
    int32_t rb1, rb2, rb3; /* interstitial readbacks, to flush buffers if needed */

    /* data buffer */
    int32_t test_addr;
    uint8_t test_buff[BUFF_SIZE];
    uint8_t read_buff[BUFF_SIZE];

    /* parse command line options */
    while ((i = getopt (argc, argv, "ht:")) != -1) {
        switch (i) {
            case 'h':
                usage();
                return EXIT_FAILURE;
                break;

            case 't':
                i = sscanf(optarg, "%i", &xi);
                if ((i != 1) || (xi < 1) || (xi > 4)) {
                    MSG("ERROR: invalid test number\n");
                    return EXIT_FAILURE;
                } else {
                    test_number = xi;
                }
                break;

            default:
                MSG("ERROR: argument parsing use -h option for help\n");
                usage();
                return EXIT_FAILURE;
        }
    }
    MSG("INFO: Starting LoRa concentrator SPI stress-test number %i\n", test_number);

    /* configure signal handling */
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_handler = sig_handler;
    sigaction(SIGQUIT, &sigact, NULL);
    sigaction(SIGINT, &sigact, NULL);
    sigaction(SIGTERM, &sigact, NULL);

    /* start SPI link */
    i = lgw_connect(false, DEFAULT_TX_NOTCH_FREQ);
    if (i != LGW_REG_SUCCESS) {
        MSG("ERROR: lgw_connect() did not return SUCCESS");
        return EXIT_FAILURE;
    }

    if (test_number == 1) {
        /* single 8b register R/W stress test */
        while ((quit_sig != 1) && (exit_sig != 1)) {
            printf("Cycle %i > ", cycle_number);
            for (i=0; i<repeats_per_cycle; ++i) {
                test_value = (rand() % 256);
                lgw_reg_w(LGW_IMPLICIT_PAYLOAD_LENGHT, test_value);
                lgw_reg_r(LGW_IMPLICIT_PAYLOAD_LENGHT, &read_value);
                if (read_value != test_value) {
                    error = true;
                    break;
                }
            }
            if (error) {
                printf("error during the %ith iteration: write 0x%02X, read 0x%02X\n", i+1, test_value, read_value);
                printf("Repeat read of target register:");
                for (i=0; i<READS_WHEN_ERROR; ++i) {
                    lgw_reg_r(LGW_IMPLICIT_PAYLOAD_LENGHT, &read_value);
                    printf(" 0x%02X", read_value);
                }
                printf("\n");
                return EXIT_FAILURE;
            } else {
                printf("did %i R/W on an 8 bits reg with no error\n", repeats_per_cycle);
                ++cycle_number;
            }
        }
    } else if (test_number == 2) {
        /* single 8b register R/W with interstitial VERSION check stress test */
        while ((quit_sig != 1) && (exit_sig != 1)) {
            printf("Cycle %i > ", cycle_number);
            for (i=0; i<repeats_per_cycle; ++i) {
                test_value = (rand() % 256);
                lgw_reg_r(LGW_VERSION, &rb1);
                lgw_reg_w(LGW_IMPLICIT_PAYLOAD_LENGHT, test_value);
                lgw_reg_r(LGW_VERSION, &rb2);
                lgw_reg_r(LGW_IMPLICIT_PAYLOAD_LENGHT, &read_value);
                lgw_reg_r(LGW_VERSION, &rb3);
                if ((rb1 != VERS) || (rb2 != VERS) || (rb3 != VERS) || (read_value != test_value)) {
                    error = true;
                    break;
                }
            }
            if (error) {
                printf("error during the %ith iteration: write %02X, read %02X, version (%i, %i, %i)\n", i+1, test_value, read_value, rb1, rb2, rb3);
                printf("Repeat read of target register:");
                for (i=0; i<READS_WHEN_ERROR; ++i) {
                    lgw_reg_r(LGW_IMPLICIT_PAYLOAD_LENGHT, &read_value);
                    printf(" 0x%02X", read_value);
                }
                printf("\n");
                return EXIT_FAILURE;
            } else {
                printf("did %i R/W on an 8 bits reg with no error\n", repeats_per_cycle);
                ++cycle_number;
            }
        }
    } else if (test_number == 3) {
        /* 32b register R/W stress test */
        while ((quit_sig != 1) && (exit_sig != 1)) {
            printf("Cycle %i > ", cycle_number);
            for (i=0; i<repeats_per_cycle; ++i) {
                test_value = (rand() & 0x0000FFFF);
                test_value += (int32_t)(rand() & 0x0000FFFF) << 16;
                lgw_reg_w(LGW_FSK_REF_PATTERN_LSB, test_value);
                lgw_reg_r(LGW_FSK_REF_PATTERN_LSB, &read_value);
                if (read_value != test_value) {
                    error = true;
                    break;
                }
            }
            if (error) {
   