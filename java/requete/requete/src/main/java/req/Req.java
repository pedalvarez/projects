package req;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.querydsl.core.annotations.QueryEntity;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import java.util.Arrays;
import java.util.Map;
import java.util.stream.Collectors;

@QueryEntity
@Document
@JsonInclude(JsonInclude.Include.ALWAYS)
public class Req {

	/**
	 * The status of the req
	 */
	public enum Status {
		ENTERED(0),
		REVIEWED(1),
		READY(2);

		private static Map<Integer, Status> intToStatus = Arrays.stream(Status.values())
				.collect(Collectors.toMap(Status::intVal, i -> i));

		private final int intVal;

		Status(int intVal) {
			this.intVal = intVal;
		}

		public int intVal() {
			return intVal;
		}

		public static Status fromInt(int intStatus) {
			final Status status = intToStatus.get(intStatus);
			if (status == null) {
				throw new IllegalArgumentException("Unknown status");
			}
			return status;
		}
	}

	@Id
	private String id;

	private String source;
	private String shortText;
	private Status status;
	private String text;
	private String given;
	private String when;
	private String then;

	@JsonProperty("id")
	private String emberId;
	public String getEmberId() {
		return id;
	}

	public String getSource() {
		return source;
	}

	public void setSource(String source) {
		this.source = source;
	}

	public String getShortText() {
		return shortText;
	}

	public void setShortText(String shortText) {
		this.shortText = shortText;
	}

	public Status getStatus() {
		return status;
	}

	public void setStatus(Status status) {
		this.status = status;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}

	public String getGiven() {
		return given;
	}

	public void setGiven(String given) {
		this.given = given;
	}

	public String getWhen() {
		return when;
	}

	public void setWhen(String when) {
		this.when = when;
	}

	public String getThen() {
		return then;
	}

	public void setThen(String then) {
		this.then = then;
	}
}
