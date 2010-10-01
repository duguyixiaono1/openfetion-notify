/***************************************************************************
 *   Copyright (C) 2010 by lwp                                             *
 *   levin108@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef FETION_LOGIN_H
#define FETION_LOGIN_H
enum
{
	PASSWORD_ERROR_MAX = 0	
};

/**
 * ssi login through https to get some information as user-id
 * @param user Global User object initialized before login
 * @return Returns the response string by ssi server 
 * 	   NULL if error occuered , need to be freed after use.
 */
extern char* ssi_auth_action(User* user);


/**
 * sipc register action to sipc server.
 * @param user Global User object initialized before login
 * @returns Returns the response string by sipc server
 * 	NULL if error occured , need to be freed after use.
 */
extern char* sipc_reg_action(User* user);

/**
 * parse the ssi registration response string to get information as user-id
 * @param ssi_response The return value of function ssi_auth_action.
 * @param user Global User object initialized before login.
 * 	The result code will be store in its member variable 'loginStatus'
 */
extern void parse_ssi_auth_response(const char* ssi_response , User* user);

/**
 * parse the sipc registration response string to get nonce string and key string
 * for sipc authentication
 * @param reg_response The return value of function sipc_auth_action
 * @param nouce Will be filled by the nonce string parsed from reg_response.
 * 	need to be freed after use.
 * @param key Will be filled by the key string parsed from reg_response.
 * 	need to be freed after use.
 */
extern void parse_sipc_reg_response(const char* reg_response , char** nouce , char** key) ;

/**
 * generate response string for sipc authentication.
 * @param nouce. Nonce string get from function "parse_sipc_reg_response()"
 * @param userid. UserId get from ssi register result.
 * @param password. Nothing special,just your password.
 * @param publickey. Key string get from function "parse_sipc_reg_response()" , which in fact unused.
 * @param key. Private key string need for generate sipc authentication response string. 
 * 	and can be generated by the function "generate_aes_key()"
 * @return The response string generated for sipc authentication.Need to be freed after use.
 */
extern char* generate_response(const char* nouce , const char* userid 
	, const char* password , const char* publickey , const char* key) ;

/**
 * sipc authentication using the response string generated by the function "generate_response()"
 * @param user Global User object initialized before login.
 * @return sipc authencation response string from sipc server.Need to be freed after use.
 */
extern char* sipc_aut_action(User* user , const char* response);

/**
 * parse the user`s personal information and user`s contact information
 *  from the sipc authentication response string.
 *  @param auth_response. Response string returns by the function "sipc_aut_action()"
 *  @user Global User object initialized before login,and will be filled with 
 *  	user`s personal information and user`s contact list information if success,
 *  	orelse the member variable "loginStatus" will be filled with errno.
 */
extern int parse_sipc_auth_response(const char* auth_response , User* user);

/**
 * generate comfirm code picture.
 */
extern void generate_pic_code(User* user);

/**
 * generate private key string for generating response string for sipc authentication
 * @returns Need to be freed after use.
 */
extern char* generate_aes_key() ;
#endif