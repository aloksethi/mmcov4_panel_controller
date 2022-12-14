/*
 * mlab_handler.c
 *
 *  Created on: Jan 26, 2021
 *      Author: asethi
 */

#include <string.h>
#include "main.h"
#include "mlab_handler.h"

#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"

#include "queue.h"

static uint8_t g_rcv_buffer[2048]; // biggest payload
static TaskHandle_t g_handle_mlab_task;

//static sensor_data_t *sensor_queue_ptr;

static uint16_t handle_command(mlab_data_t *raw_data_p) {
	uint16_t data_to_return = 0;

	switch (raw_data_p->command_code) {

	case G_UC_SET_REG_CONFIG: {
		uint8_t ic_id;
		uint8_t i, num_chunks; //number of chunks of sub data
		reg_t *local_reg_ptr;

		pc_queue_data_t queue_post;

		trace_printf("command: set_reg \n");

		ic_id = raw_data_p->ic_id;
		num_chunks = raw_data_p->num_chunks;
		for (i = 0; i < num_chunks; i++) {
			//&raw_data_p->data[0] is a pointer to void and is of size 4, so adding 2 will increment it by8
			local_reg_ptr = (reg_t*) ((uint8_t*) (&raw_data_p->data[0])
					+ i * sizeof(reg_t));
			pc_set_curr_value(ic_id, local_reg_ptr);

			queue_post.command_code = G_UC_SET_REG_CONFIG;
			queue_post.ic_id = ic_id;
			queue_post.reg_id = local_reg_ptr->reg_id;

			xQueueSendToBack(g_pc_queue_handle, &queue_post, portMAX_DELAY);
		}
		break;
	}

	case G_UC_SAVE_DEF_REG_CONFIG: {
		uint8_t ic_id;
		uint8_t i, num_chunks; //number of chunks of sub data
		reg_t *local_reg_ptr;

		ic_id = raw_data_p->ic_id;
		num_chunks = raw_data_p->num_chunks;

		trace_printf("command: save_def, num_chunks:%d \n", num_chunks);
		for (i = 0; i < num_chunks; i++) {
			local_reg_ptr = (reg_t*) ((uint8_t*) (&raw_data_p->data[0])
					+ i * sizeof(reg_t));
			pc_save_default_value(ic_id, local_reg_ptr);
		}
		break;
	}

	case G_UC_SAVE_MINI_REG_CONFIG: {
		uint8_t ic_id;
		uint8_t i, num_chunks; //number of chunks of sub data
		reg_t *local_reg_ptr;

		trace_printf("command: save_mini \n");

		ic_id = raw_data_p->ic_id;
		num_chunks = raw_data_p->num_chunks;
		for (i = 0; i < num_chunks; i++) {
			local_reg_ptr = (reg_t*) ((uint8_t*) (&raw_data_p->data[0])
					+ i * sizeof(reg_t));
			pc_save_mini_value(ic_id, local_reg_ptr);
		}
		break;
	}

	case G_UC_SAVE_MAXI_REG_CONFIG: {
		uint8_t ic_id;
		uint8_t i, num_chunks; //number of chunks of sub data
		reg_t *local_reg_ptr;

		trace_printf("command: save_maxi \n");

		ic_id = raw_data_p->ic_id;
		num_chunks = raw_data_p->num_chunks;
		for (i = 0; i < num_chunks; i++) {
			local_reg_ptr = (reg_t*) ((uint8_t*) (&raw_data_p->data[0])
					+ i * sizeof(reg_t));
			pc_save_maxi_value(ic_id, local_reg_ptr);
		}
		break;
	}

	case G_UC_APPLY_DEF_REG_CONFIG: {
		uint8_t ic_id;
		pc_queue_data_t queue_post;

		trace_printf("command: apply_def \n");

		ic_id = raw_data_p->ic_id;
		queue_post.command_code = G_UC_APPLY_DEF_REG_CONFIG;
		queue_post.ic_id = ic_id;
//			queue_post.reg_id = local_reg_ptr->reg_id;

		xQueueSendToBack(g_pc_queue_handle, &queue_post, portMAX_DELAY);
		break;
	}

	case G_UC_APPLY_MAXI_REG_CONFIG: {
		uint8_t ic_id;
		pc_queue_data_t queue_post;

		trace_printf("command: apply_maxi \n");

		ic_id = raw_data_p->ic_id;
		queue_post.command_code = G_UC_APPLY_MAXI_REG_CONFIG;
		queue_post.ic_id = ic_id;
//			queue_post.reg_id = local_reg_ptr->reg_id;

		xQueueSendToBack(g_pc_queue_handle, &queue_post, portMAX_DELAY);
		break;
	}

	case G_UC_APPLY_MINI_REG_CONFIG: {
		uint8_t ic_id;
		pc_queue_data_t queue_post;

		trace_printf("command: apply_def \n");

		ic_id = raw_data_p->ic_id;
		queue_post.command_code = G_UC_APPLY_MINI_REG_CONFIG;
		queue_post.ic_id = ic_id;
//			queue_post.reg_id = local_reg_ptr->reg_id;

		xQueueSendToBack(g_pc_queue_handle, &queue_post, portMAX_DELAY);
		break;
	}

	case G_UC_SYNTH_POWER: {
		uint32_t val;

		trace_printf("command: synth_power \n");
		val = (uint8_t) (raw_data_p->data[0]); // make power value out of pointer
		if (val)
			board_synth_power_on();
		else
			board_synth_power_off();

		break;
	}

	case G_UC_SYNTH_CONFIG: {
		synth_config_data_t *local_reg_ptr;
		uint8_t synth_id, reg;
		uint16_t val;

		trace_printf("command: synth_config\n");

		local_reg_ptr = (synth_config_data_t*) (&raw_data_p->data[0]);


		synth_id = local_reg_ptr->synth_id;
		reg = local_reg_ptr->reg_num;
		val = local_reg_ptr->data;

		trace_printf("synth:%d reg:%x val:%x\n", synth_id, reg, val);
		board_synth_write_reg(local_reg_ptr);

		board_synth_read_reg(local_reg_ptr);


		break;
	}

	case G_UC_3V3_POWER: {
		uint32_t val;

		trace_printf("command: 3V3_power \n");
		// sender is sending only one byte, by using uint32 more other garbage values are alos used for getting
		// the value of 'val'
		val = (uint8_t) (raw_data_p->data[0]); // make power value out of pointer
		if (val)
			board_3v3_power_on();
		else
			board_3v3_power_off();

		break;
	}

	case G_UC_1V0_POWER: {
		uint8_t ic_id;
		pow1_1v_data_t *local_reg_ptr;
		val_1v_t val;

		ic_id = raw_data_p->ic_id;
		local_reg_ptr = (pow1_1v_data_t*) (&raw_data_p->data[0]);
		val = local_reg_ptr->val;

		trace_printf("command: 1V power supply \n");

		board_1v_control(ic_id, val);
		break;
	}

	case G_UC_1V5_POWER: {

		val_1v5_t *pval;

		pval = (val_1v5_t*) (&raw_data_p->data[0]);

		trace_printf("command: 1V5 power supply, val:%d \n", *pval);

		shreg_set_1V5_en(*pval);
		break;
	}

	case G_UC_2V75_POWER: {

		val_1v5_t *pval;

		pval = (val_1v5_t*) (&raw_data_p->data[0]);

		trace_printf("command: 2V75 power supply, val:%d \n", *pval);

		shreg_set_2V75_en(*pval);
		break;
	}

	case G_UC_REFCLK: {
		synth_refclk_data_t *local_reg_ptr;
		val_gen_t val;
		uint8_t synth_id;

		local_reg_ptr = (synth_refclk_data_t*) (&raw_data_p->data[0]);
		val = local_reg_ptr->val;
		synth_id = local_reg_ptr->synth_id;

		trace_printf(
				"command: synthesizer refclk enable/disable, synth:%d en:%d\n",
				synth_id, val);

		shref_set_synth_refclk(synth_id, val);
		break;
	}

	case G_UC_IREF: {
		uint8_t ic_id;
		val_iref_t *pval;

		ic_id = raw_data_p->ic_id;
		pval = (val_iref_t*) (&raw_data_p->data[0]);

		trace_printf("command: iref enable/disable, icid:%d en:%d\n", ic_id,
				*pval);

		shreg_set_iref(ic_id, (val_gen_t) *pval);
		break;
	}

	case G_UC_RX_BB_SW: {
		uint8_t ic_id;
		val_iref_t *pval;

		ic_id = raw_data_p->ic_id;
		pval = (val_iref_t*) (&raw_data_p->data[0]);

		trace_printf("command: BB SW enable/disable, icid:%d en:%d\n", ic_id,
				*pval);

		shreg_set_bb_sw(ic_id, (val_gen_t) *pval);
		break;
	}
	case G_UC_RX_BB_AMP: {
		uint8_t ic_id;
		val_iref_t *pval;

		ic_id = raw_data_p->ic_id;
		pval = (val_iref_t*) (&raw_data_p->data[0]);

		trace_printf("command: BB amp enable/disable, icid:%d en:%d\n", ic_id,
				*pval);

		shreg_set_bb_amp(ic_id, (val_gen_t) *pval);
		break;
	}
	case G_UC_2V0_POWER:

	case G_UC_PA_GATE_BIAS:
		trace_printf("TODO:command not implemented yet\n");
		break;
#if 0
	case G_UC_PB_SENSORS:
	{
		trace_printf("command: get pb sensors\n");
		xTaskNotifyGive(g_handle_sensor_task);

		if (xQueueReceive(g_sensor_queue_handle, &sensor_queue_ptr,
				(300 / portTICK_PERIOD_MS)) == pdPASS)
		{
			data_to_return = sizeof(sensor_data_t);
		}
		else
			data_to_return = 0;

		break;
	}
#endif
	}

	return data_to_return;
}
static uint8_t sanity_check(mlab_data_t *raw_data_p) {
	uint8_t sane = 0;

	if ((raw_data_p->command_code <= G_UC_MIN_COMMAND_CODE)
			|| (raw_data_p->command_code >= G_UC_MAX_COMMAND_CODE)) {
		trace_printf("invalid command code : %d\n", raw_data_p->command_code);
		sane = 0;
		return sane;
	}

	if ((raw_data_p->ic_id == 0) || (raw_data_p->ic_id > G_MAX_ICS_PER_UC)) {
		trace_printf("invalid ic_id\n");
		sane = 0;
		return sane;
	}

	if ((raw_data_p->num_chunks > G_MAX_NUM_REGS)) //num_chunks is 0 for apply_preset_config
	{
		trace_printf("invalid num_chunks\n");
		sane = 0;
		return sane;
	}

	if (raw_data_p->command_code == G_UC_SET_REG_CONFIG) {
		uint8_t num_regs, i;

		num_regs = raw_data_p->num_chunks;

		if (num_regs == 0) {
			trace_printf("invalid number of registers in the buffer\n");
			sane = 0;
			return sane;
		}
		for (i = 0; i < num_regs; i++) {
			reg_t *local_reg_ptr;
			uint8_t reg_id, cascade;

			local_reg_ptr = (reg_t*) (&raw_data_p->data[0] + i * sizeof(reg_t));
			reg_id = local_reg_ptr->reg_id;
			cascade = local_reg_ptr->cascade;

			if ((cascade > G_REGS_PER_REG) || (reg_id > G_MAX_NUM_REGS)) {
				trace_printf("invalid arguments\n");
				sane = 0;
				return sane;
			}
		}
	}

	if (raw_data_p->command_code == G_UC_1V0_POWER) {
		pow1_1v_data_t *local_reg_ptr;
		uint8_t num_chunks;
		pow_plane_t plane_id; //number of chunks of sub data
		val_1v_t val;

		num_chunks = raw_data_p->num_chunks;
		if (num_chunks) {
			sane = 0;
			trace_printf("only one chunk allowed\n");
			return sane;
		}
		local_reg_ptr = (pow1_1v_data_t*) (&raw_data_p->data[0]);
		plane_id = board_icid_to_pow_plane(raw_data_p->ic_id);

		val = local_reg_ptr->val;

		switch (plane_id) {
		case R1:
		case R2:
		case R3:
		case R4:
			break;
		default:
			sane = 0;
			trace_printf("invalid plane id\n");
			return sane;
		}

		switch (val) {
		case V_0V00:
		case V_0V80:
		case V_0V85:
		case V_0V90:
		case V_0V95:
		case V_1V00:
		case V_1V05:
		case V_1V10:
		case V_1V15:
		case V_1V20:
			break;
		default:
			sane = 0;
			trace_printf("invalid value \n");
			return sane;
		}
	}

	if (raw_data_p->command_code == G_UC_REFCLK) {
		synth_refclk_data_t *local_reg_ptr;
		//val_gen_t val;
		uint8_t synth_id;

		local_reg_ptr = (synth_refclk_data_t*) (&raw_data_p->data[0]);
		//val = local_reg_ptr->val;
		synth_id = local_reg_ptr->synth_id;

		if ((synth_id > 2) || (synth_id < 1)) {
			trace_printf("invalid synthesizer ID\n");
			sane = 0;
			return sane;
		}
	}

	if ((raw_data_p->command_code == G_UC_RX_BB_SW)
			|| (raw_data_p->command_code == G_UC_RX_BB_AMP)) {
		uint8_t ic_id = raw_data_p->ic_id;

		if (!((ic_id == 1) || (ic_id == 6) || (ic_id == 11) || (ic_id == 16))) {
			trace_printf("invalid ic_id for this command\n");
			sane = 0;
			return sane;
		}
	}

	sane = 1;
	return sane;
}

static portTASK_FUNCTION( vMlabHandlerTask, pvParameters ) {
	/* The parameters are not used. */
	(void) pvParameters;

	static struct netconn *conn;
	static struct netbuf *buf;
//	static ip_addr_t *addr;
//	static unsigned short port;
	err_t err;
	char ret_data[4];
	void *ptr_payload = NULL;

	conn = netconn_new(NETCONN_UDP);
	LWIP_ASSERT("con != NULL", conn != NULL);
	netconn_bind(conn, NULL, G_NUCLEO_PORT_NUM);

	while (1) {
		err = netconn_recv(conn, &buf);
		if (err == ERR_OK) {
			mlab_data_t *raw_data_p;
			uint8_t sane;
			uint16_t len;
			uint32_t running_id;
			uint16_t data_to_return;
			uint16_t tot_amt_to_return;

//			addr = netbuf_fromaddr(buf);
//			port = netbuf_fromport(buf);
			//netconn_connect(conn, addr, port);
			if (sizeof(g_rcv_buffer) <= buf->p->tot_len) {
				trace_printf("total packet bigger than available buffer\n");
				Error_Handler();
			}
			netbuf_copy(buf, g_rcv_buffer, buf->p->tot_len);

//			trace_printf("rcvd udp, src_port:%d, ipaddr:", port);
			ip4_addr_debug_print(LWIP_DBG_ON, addr);
			trace_printf("\n");

			//g_rcv_buffer[buf->p->tot_len] = '\0';

			raw_data_p = (mlab_data_t*) (&g_rcv_buffer[0]);
			running_id = ntohl(raw_data_p->running_id);

			sane = sanity_check(raw_data_p);

			if (sane) {
				strcpy(ret_data, "OK");
				data_to_return = handle_command(raw_data_p);
			} else {
				strcpy(ret_data, "NOK");
			}

			netbuf_data(buf, &ptr_payload, &len);
			//trace_printf("len of buf=%d\n", len);
			tot_amt_to_return = data_to_return + sizeof(running_id)
					+ sizeof(ret_data);
			if (len < tot_amt_to_return) {
				//trace_printf("FIXME:less bytes availabel");
				netbuf_free(buf);
				ptr_payload = netbuf_alloc(buf, tot_amt_to_return);
			}

			if (NULL != ptr_payload) {
				*(uint32_t*) (ptr_payload) = htonl(running_id);
//				memcpy(ptr_payload + sizeof(running_id), ret_data,
//						sizeof(ret_data) + sizeof(uint32_t));
				memcpy(ptr_payload + sizeof(running_id), ret_data,
						sizeof(ret_data));
				if (data_to_return) {
					trace_printf("no data to return");
#if 0
					memcpy(ptr_payload + sizeof(running_id) + sizeof(ret_data),
							sensor_queue_ptr, sizeof(sensor_data_t));
#endif
				}
				buf->p->tot_len = tot_amt_to_return;
				buf->p->len = tot_amt_to_return;

				netconn_send(conn, buf);
				//LWIP_DEBUGF(LWIP_DBG_ON, ("got %s\n", buffer));
				netbuf_delete(buf);

			} else {
				trace_printf("unable to allocate return data \n");
			}

		}
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

void vStartMlabHandlerTask(UBaseType_t uxPriority) {
	BaseType_t xReturned;

	xReturned = xTaskCreate(vMlabHandlerTask, "MLABHx",
	MATLAB_HANLDER_STACK_SIZE, NULL, uxPriority,
			(TaskHandle_t*) &g_handle_mlab_task);
	if (xReturned != pdPASS) {
		/* The task was created.  Use the task's handle to delete the task. */
		trace_printf("failed to create the matlab handler task\n");
	}
}
