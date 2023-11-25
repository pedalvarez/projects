/*
 * Copyright 2016 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package req;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.ResultActions;

import static org.hamcrest.Matchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class ApplicationTests {

	@Autowired
	private MockMvc mockMvc;

	@Autowired
	private ReqRepository reqRepository;

	@Before
	public void deleteAllBeforeTests() throws Exception {
		reqRepository.deleteAll();
	}

	@Test
	@Ignore
	public void shouldReturnRepositoryIndex() throws Exception {

		mockMvc.perform(get("/")).andDo(print()).andExpect(status().isOk()).andExpect(
				jsonPath("$._links.req").exists());
	}

	@Test
	public void shouldCreateEntity() throws Exception {

		mockMvc.perform(post("/req").content(
				"{\"source\" : \"Amalia\",  \"shortText\" : \"Girl\",  \"status\" : \"0\",  \"text\" : \"abcd\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}")).andExpect(
						status().isCreated()).andExpect(
								header().string("Location", containsString("req/")));
	}

	@Test
	public void shouldRetrieveEntity() throws Exception {

		MvcResult mvcResult = mockMvc.perform(post("/req").content(
				"{\"source\" : \"Amalia\",  \"shortText\" : \"Girl\",  \"status\" : \"0\",  \"text\" : \"abcd\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}")).andExpect(
						status().isCreated()).andReturn();

		String location = mvcResult.getResponse().getHeader("Location");
		mockMvc.perform(get(location)).andExpect(status().isOk()).andExpect(
				jsonPath("$.source").value("Amalia")).andExpect(
						jsonPath("$.shortText").value("Girl"));
	}

	@Test
	public void shouldQueryEntity() throws Exception {

		mockMvc.perform(post("/req").content(
				"{ \"source\" : \"Amalia\",  \"shortText\" : \"Girl\",  \"status\" : \"0\",  \"text\" : \"abcd\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}")).andExpect(
						status().isCreated());

		ResultActions resultActions = mockMvc.perform(
				get("/req/search/findBySource?name={name}", "Amalia"));

		resultActions.andExpect(
						status().isOk()).andExpect(
								jsonPath("content[0].source").value(
										"Amalia"));
	}

	@Test
	public void shouldUpdateEntity() throws Exception {

		MvcResult mvcResult = mockMvc.perform(post("/req").content(
				"{\"source\" : \"Amalia\",  \"shortText\" : \"Girl\",  \"status\" : \"0\",  \"text\" : \"abcd\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}")).andExpect(
						status().isCreated()).andReturn();

		String location = mvcResult.getResponse().getHeader("Location");

		mockMvc.perform(put(location).content(
				"{\"source\": \"Pierre\", \"shortText\":\"Boy\"}")).andExpect(
						status().isOk());

		mockMvc.perform(get(location)).andExpect(status().isOk()).andExpect(
				jsonPath("$.source").value("Pierre")).andExpect(
						jsonPath("$.shortText").value("Boy"));
	}

	@Test
	public void shouldPartiallyUpdateEntity() throws Exception {

		MvcResult mvcResult = mockMvc.perform(post("/req").content(
				"{\"source\" : \"Amalia\",  \"shortText\" : \"Girl\",  \"status\" : \"0\",  \"text\" : \"abcd\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}")).andExpect(
						status().isCreated()).andReturn();

		String location = mvcResult.getResponse().getHeader("Location");

		mockMvc.perform(
				patch(location).content("{\"source\": \"Pierre's girl\"}")).andExpect(
						status().isOk());

		mockMvc.perform(get(location)).andExpect(status().isOk()).andExpect(
				jsonPath("$.source").value("Pierre's girl")).andExpect(
						jsonPath("$.shortText").value("Girl"));
	}

	@Test
	public void shouldDeleteEntity() throws Exception {

		MvcResult mvcResult = mockMvc.perform(post("/req").content(
				"{ \"source\" : \"Pierre's girl\",  \"shortText\" : \"Girl\",  \"status\" : \"0\",  \"text\" : \"abcd\" ,  \"given\" : \"a\", \"when\" : \"b\",  \"then\" : \"c\"}")).andExpect(
						status().isCreated()).andReturn();

		String location = mvcResult.getResponse().getHeader("Location");
		mockMvc.perform(delete(location)).andExpect(status().isNoContent());

		mockMvc.perform(get(location)).andExpect(status().isNotFound());
	}
}