/* main.c
 * Copyright (C) 2009-2022 Dale Whittaker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <mailtc.h>

#include <config.h>
#include <gmodule.h>

#define MAILTC_TYPE_EXAMPLE            (mailtc_example_get_type  ())
#define MAILTC_EXAMPLE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAILTC_TYPE_EXAMPLE, MailtcExample))
#define MAILTC_EXAMPLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  MAILTC_TYPE_EXAMPLE, MailtcExampleClass))
#define MAILTC_IS_EXAMPLE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MAILTC_TYPE_EXAMPLE))
#define MAILTC_IS_EXAMPLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  MAILTC_TYPE_EXAMPLE))
#define MAILTC_EXAMPLE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  MAILTC_TYPE_EXAMPLE, MailtcExampleClass))

#define EXTENSION_NAME        "Example"
#define EXTENSION_AUTHOR      "Dale Whittaker ("PACKAGE_BUGREPORT")"
#define EXTENSION_DESCRIPTION "Example network extension."

typedef struct
{
    MailtcExtension parent_instance;
} MailtcExample;

typedef struct
{
    MailtcExtensionClass parent_class;
} MailtcExampleClass;

MAILTC_DEFINE_EXTENSION (MailtcExample, mailtc_example)

static void
mailtc_example_finalize (GObject* object)
{
    G_OBJECT_CLASS (mailtc_example_parent_class)->finalize (object);
}

static gboolean
mailtc_example_add_account (MailtcExample* example,
                            GObject*       account,
                            GError**       error)
{
    gchar* extname = NULL;
    gchar* accname = NULL;

    (void) error;

    MAILTC_OBJECT_GET_PROPERTY (example, MAILTC_EXTENSION_PROPERTY_NAME, extname);
    MAILTC_OBJECT_GET_PROPERTY (account, MAILTC_ACCOUNT_PROPERTY_NAME, accname);

    g_print ("%s : adding account %s\n", extname, accname);

    g_free (accname);
    g_free (extname);

    return TRUE;
}

static gboolean
mailtc_example_remove_account (MailtcExample* example,
                               GObject*       account,
                               GError**       error)
{
    gchar* extname = NULL;
    gchar* accname = NULL;

    (void) error;

    MAILTC_OBJECT_GET_PROPERTY (example, MAILTC_EXTENSION_PROPERTY_NAME, extname);
    MAILTC_OBJECT_GET_PROPERTY (account, MAILTC_ACCOUNT_PROPERTY_NAME, accname);

    g_print ("%s : removing account %s\n", extname, accname);

    g_free (accname);
    g_free (extname);

    return TRUE;
}

static gint64
mailtc_example_get_messages (MailtcExample* example,
                             GObject*       account,
                             gboolean       debug,
                             GError**       error)
{
    gint64 nmessages;
    gchar* extname = NULL;
    gchar* accname = NULL;

    (void) debug;
    (void) error;

    MAILTC_OBJECT_GET_PROPERTY (example, MAILTC_EXTENSION_PROPERTY_NAME, extname);
    MAILTC_OBJECT_GET_PROPERTY (account, MAILTC_ACCOUNT_PROPERTY_NAME, accname);

    nmessages = g_random_int_range (0, 100);

    g_print ("%s : got %" G_GINT64_FORMAT " messages from %s\n", extname, nmessages, accname);

    g_free (accname);
    g_free (extname);

    return nmessages;
}

static gboolean
mailtc_example_read_messages (MailtcExample* example,
                              GObject*       account,
                              GError**       error)
{
    gchar* extname = NULL;
    gchar* accname = NULL;

    (void) error;

    MAILTC_OBJECT_GET_PROPERTY (example, MAILTC_EXTENSION_PROPERTY_NAME, extname);
    MAILTC_OBJECT_GET_PROPERTY (account, MAILTC_ACCOUNT_PROPERTY_NAME, accname);

    g_print ("%s : read messages for account %s\n", extname, accname);

    g_free (accname);
    g_free (extname);

    return TRUE;
}

static void
mailtc_example_class_init (MailtcExampleClass* klass)
{
    GObjectClass* gobject_class;
    MailtcExtensionClass* extension_class;

    gobject_class = G_OBJECT_CLASS (klass);
    gobject_class->finalize = mailtc_example_finalize;

    extension_class = MAILTC_BASE_EXTENSION_CLASS (klass);
    extension_class->add_account = (MailtcExtensionAddAccountFunc) mailtc_example_add_account;
    extension_class->remove_account = (MailtcExtensionRemoveAccountFunc) mailtc_example_remove_account;
    extension_class->read_messages = (MailtcExtensionReadMessagesFunc) mailtc_example_read_messages;
    extension_class->get_messages = (MailtcExtensionGetMessagesFunc) mailtc_example_get_messages;
}

static void
mailtc_example_init (MailtcExample* example)
{
    (void) example;
}

static MailtcExample*
mailtc_example_new (const gchar* directory)
{
    MailtcExample* example;
    GArray* protocol_array;

    MailtcProtocol protocols[] =
    {
        { "Example Protocol A", 123 },
        { "Example Protocol B", 456 },
    };

    protocol_array = g_array_new (TRUE, FALSE, sizeof (MailtcProtocol));
    g_array_append_vals (protocol_array, protocols, 2);

    example = g_object_new (MAILTC_TYPE_EXAMPLE,
                            MAILTC_EXTENSION_PROPERTY_DIRECTORY,     directory,
                            MAILTC_EXTENSION_PROPERTY_COMPATIBILITY, VERSION,
                            MAILTC_EXTENSION_PROPERTY_NAME,          EXTENSION_NAME,
                            MAILTC_EXTENSION_PROPERTY_AUTHOR,        EXTENSION_AUTHOR,
                            MAILTC_EXTENSION_PROPERTY_DESCRIPTION,   EXTENSION_DESCRIPTION,
                            MAILTC_EXTENSION_PROPERTY_PROTOCOLS,     protocol_array,
                            NULL);

    g_array_unref (protocol_array);

    return example;
}

G_MODULE_EXPORT GSList*
extension_init (const gchar* directory)
{
    return g_slist_append (NULL, mailtc_example_new (directory));
}

