package req;


import com.querydsl.core.types.Predicate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.constraints.Min;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.ws.rs.*;
import java.util.List;

import static java.util.stream.Collectors.toList;

@RestController
@Produces("application/json")
@RequestMapping("/req/suggest")
public class SuggestResource {


    @Autowired
    private ReqRepository reqRepository;

    @GET
    @RequestMapping("/sources")
    public List<String> suggestSources(@QueryParam("prefix") @NotNull @Size(min = 0) String prefix,
                                       @DefaultValue("8") @QueryParam("limit") @Min(1) int limit) {

        QReq qReq = new QReq("req");
        Predicate predicate = qReq.source.startsWith(prefix);
                return ((List<Req>) reqRepository.findAll(predicate)).stream().limit(limit).map(Req::getSource).collect(toList());
    }

    @GET
    @RequestMapping("/shortTexts")
    public List<String> suggestShortTexts(@QueryParam("prefix") @NotNull @Size(min = 0) String prefix,
                                       @DefaultValue("8") @QueryParam("limit") @Min(1) int limit) {

        QReq qReq = new QReq("req");
        Predicate predicate = qReq.shortText.startsWith(prefix);
        return ((List<Req>) reqRepository.findAll(predicate)).stream().limit(limit).map(Req::getShortText).collect(toList());
    }

}
