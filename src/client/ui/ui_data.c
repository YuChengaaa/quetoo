/*
 * Copyright(c) 1997-2001 Id Software, Inc.
 * Copyright(c) 2002 The Quakeforge Project.
 * Copyright(c) 2006 Quake2World.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "ui_local.h"
#include "client.h"

extern cl_static_t cls;

/*
 * @brief Callback setting a cvar_t's string.
 */
static void TW_CALL Ui_CvarSetString(const void *value, void *data) {
	cvar_t *var = (cvar_t *) data;
	const char *val = (const char *) value;

	Cvar_Set(var->name, val);
}

/*
 * @brief Callback exposing a cvar_t's string.
 */
static void TW_CALL Ui_CvarGetString(void *value, void *data) {
	cvar_t *var = (cvar_t *) data;
	char *val = (char *) value;

	strcpy(val, var->string);
}

/*
 * @brief Exposes a cvar_t as a text input accepting strings.
 */
void Ui_CvarText(TwBar *bar, const char *name, cvar_t *var, const char *def) {
	TwAddVarCB(bar, name, TW_TYPE_CSSTRING(128), Ui_CvarSetString, Ui_CvarGetString, var, def);
}

/*
 * @brief Callback setting a cvar_t's integer.
 */
static void TW_CALL Ui_CvarSetInteger(const void *value, void *data) {
	cvar_t *var = (cvar_t *) data;

	Cvar_Set(var->name, va("%d", *(int32_t *) value));
}

/*
 * @brief Callback exposing a cvar_t's integer.
 */
static void TW_CALL Ui_CvarGetInteger(void *value, void *data) {
	cvar_t *var = (cvar_t *) data;
	*(int32_t *) value = var->integer;
}

/*
 * @brief Exposes a cvar_t as a text input accepting integers.
 */
void Ui_CvarInteger(TwBar *bar, const char *name, cvar_t *var, const char *def) {
	TwAddVarCB(bar, name, TW_TYPE_INT32, Ui_CvarSetInteger, Ui_CvarGetInteger, var, def);
}

/*
 * @brief Exposes a cvar_t as a select input with predefined numeric values.
 */
void Ui_CvarEnum(TwBar *bar, const char *name, cvar_t *var, TwType en, const char *def) {
	TwAddVarCB(bar, name, en, Ui_CvarSetInteger, Ui_CvarGetInteger, var, def);
}

/*
 * @brief Callback setting a cvar_t's value.
 */
static void TW_CALL Ui_CvarSetValue(const void *value, void *data) {
	cvar_t *var = (cvar_t *) data;

	Cvar_Set(var->name, va("%f", *(vec_t *) value));
}

/*
 * @brief Callback exposing a cvar_t's value.
 */
static void TW_CALL Ui_CvarGetValue(void *value, void *data) {
	cvar_t *var = (cvar_t *) data;
	*(vec_t *) value = var->value;
}

/*
 * @brief Exposes a cvar_t as a text input accepting decimals.
 */
void Ui_CvarDecimal(TwBar *bar, const char *name, cvar_t *var, const char *def) {
	TwAddVarCB(bar, name, TW_TYPE_FLOAT, Ui_CvarSetValue, Ui_CvarGetValue, var, def);
}

/*
 * @brief Stuffs the specified text onto the command buffer.
 */
void TW_CALL Ui_Command(void *data) {
	Cbuf_AddText((const char *) data);
}

/*
 * @brief Binds the key specified in value to the command specified in data.
 */
static void TW_CALL Ui_BindSet(const void *value, void *data) {
	Cl_Bind(atoi( (char *) value), (char *) data);
}

/*
 * @brief Copies the key names for the bind specified in data to value.
 */
static void TW_CALL Ui_BindGet(void *value, void *data) {
	char **binds = cls.key_state.binds;
	char *bind = (char *) data;
	SDLKey i;

	char *s = (char *) value;
	*s = 0;

	for (i = SDLK_FIRST; i < (SDLKey) SDLK_MLAST; i++) {
		if (binds[i] && !g_ascii_strcasecmp(bind, binds[i])) {
			strcat(s, va(strlen(s) ? ", %s" : "%s", Cl_KeyName(i)));
		}
	}
}

/*
 * @brief Exposes a key binding via the specified TwBar.
 */
void Ui_Bind(TwBar *bar, const char *name, const char *bind, const char *def) {
	TwAddVarCB(bar, name, TW_TYPE_BIND, Ui_BindSet, Ui_BindGet, (void *) bind, def);
}
