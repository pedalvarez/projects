
package req;

import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.querydsl.QueryDslPredicateExecutor;
import org.springframework.data.repository.query.Param;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

import java.util.List;

@RepositoryRestResource(collectionResourceRel = "req", path = "req")
public interface ReqRepository extends MongoRepository<Req, String> , QueryDslPredicateExecutor<Req> {
    List<Req> findBySource(@Param("name") String name);
}
